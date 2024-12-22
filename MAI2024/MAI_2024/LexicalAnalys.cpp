#include "stdafx.h"

using namespace std;

namespace Lex
{
	int Oct_to_dec(char* s)
	{
		int res = 0;
		for (int i = 2; s[i] != NULL; ++i)
		{
			res *= 8;
			res += (s[i] - '0'); // Прибавление значения, соответствующего текущей цифре в восьмеричной системе (вычитание кода символа '0')
		}
		return res;
	}
	int Bin_to_dec(char* s)
	{
		int res = 0;
		for (int i = 2; s[i] != NULL; ++i)
		{
			res *= 2;
			res += (s[i] - '0');
		}
		return res;
	}

	void ITLog(IT::IdTable it, Log::LOG log)
	{
		int i, numberOP = 0;
		*log.stream << "\nТаблица идентификаторов:\n\n";
		*log.stream << "№   " << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << " Значение   " << endl;
		*log.stream << setw(87) << endl;
		for (i = 0; i < it.size; i++)
		{
			*log.stream << setfill('0') << setw(4) << right << i << "    ";
			*log.stream << setfill(' ') << setw(13) << left << it.table[i].id;
			switch (it.table[i].iddatatype)
			{
			case IT::INT: *log.stream << setw(10) << left;
				if (it.table[i].idtype == IT::OP)*log.stream << "-";
				else *log.stream << "integer   "; break;
			case IT::STR: *log.stream << setw(10) << left;
				if (it.table[i].idtype == IT::OP) *log.stream << "-";
				else *log.stream << "string    "; break;
			default: *log.stream << setw(10) << std::left << "unknown"; break;
			}
			switch (it.table[i].idtype)
			{
			case IT::V: *log.stream << left << "переменная     "; break;
			case IT::F: *log.stream << left << "функция        "; break;
			case IT::P: *log.stream << left << "параметр       "; break;
			case IT::L: *log.stream << left << "литерал        "; break;
			case IT::OP: *log.stream << left << "оператор       "; break;
				break;
			default: *log.stream << left << "unknown        "; break;
			}
			*log.stream << setw(11) << left << it.table[i].idxfirstLE;
			if (it.table[i].iddatatype == IT::INT && (it.table[i].idtype == IT::V || it.table[i].idtype == IT::L))
				*log.stream << setw(18) << left << it.table[i].value.vint;
			else if (it.table[i].iddatatype == IT::STR && (it.table[i].idtype == IT::V || it.table[i].idtype == IT::L))
				*log.stream << "[" << it.table[i].value.vstr->len << "]" << " \"" << it.table[i].value.vstr->str << "\" " << "";
			else if (it.table[i].idtype == IT::OP)
				*log.stream << setw(18) << left << it.table[i].value.op;
			else
				*log.stream << "       -       ";
			*log.stream << endl;
		}

		*log.stream << "\nКоличество идентификаторов:\n " << i << endl;

	}


	void LTLog(LT::LexTable lt, Log::LOG log)
	{

		int line = 1;
		*log.stream << "\n";
		*log.stream << "Таблица лексем:\n\n";
		*log.stream << line << "  ";
		for (int i = 0; i < lt.size; i++)
		{
			if (lt.table[i].lexema[0] == ';' || lt.table[i].lexema[0] == '[')
			{
				*log.stream << lt.table[i].lexema[0];
				line++;
				*log.stream << '\n';
				*log.stream << line << "  ";
				continue;
			}
			*log.stream << lt.table[i].lexema[0];
		}
	}

	LEX LexicalAnalysis(Log::LOG log, In::IN in, vector<ffst::FST>& fsts)
	{
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);
		IT::Entry entryIT;

		int cHead = 0;
		int line = 1;
		int position = 0;
		int indxLex = 0;
		int indexID = 0;
		int cLit = 1;
		int cOperators = 1;


		bool findFunc = false;
		bool findInt = false;
		bool findString = false;
		bool findParm = false;
		bool findHead = false;
		bool findSameID = false;
		bool findNew = false;
		bool findBlock = false;
		bool findStandart = false;
		bool findUntil = false;

		char emptystr[] = "";
		char operators[] = "=+-*/%";

		char* L = new  char[2] { "L" };              // Префикс для литералов
		char* OP = new  char[3] { "OP" };            // Префикс для операторов
		char* bufL = new  char[TI_STR_MAXSIZE];     // Буфер для формирования имени литерала
		char* nameLiteral = new  char[10] { "" };    // Имя литерала
		char* charclit = new char[10] { "" };        // Буфер для конвертации числа в строку
		char* prefix = new  char[10] { "" };         // Префикс для идентификаторов
		char* bufprefix = new  char[10] { "" };      // Буфер для формирования имени идентификатора
		char* oldprefix = new  char[10] { "" };      // Старый префикс, используется при обработке стандартных функций


		auto addLexeme = [&line, &lextable, &indxLex](char lexeme, int priority = 0) -> void // добавление в табл лксм с приоритетом
			{
				LT::Entry entryLT = WriteEntry(entryLT, lexeme, LT_TI_NULLIDX, line);
				entryLT.priority = priority;
				indxLex++;
				LT::Add(lextable, entryLT);
			};

		char* word[max_word];  // Объявление массива указателей на строки (массив слов) размером max_word
		for (int i = 0; i < max_word; i++)
			word[i] = new char[size_word] {NULL};
		// Динамическое выделение памяти под каждое слово в массиве.
		// Каждое слово может содержать до size_word символов (включая завершающий нуль), инициализация нулями.

		for (int i = 0; i < max_word; i++)
			std::strcpy(word[i], SplitText((char*)in.text, in.size)[i]);
		// Заполнение массива слов значениями, полученными при помощи функции SplitText.

// Пояснение к SplitText:
// SplitText((char*)in.text, in.size) разделяет текст in.text на отдельные слова и возвращает массив строк (символьных массивов).
// [i] обращается к i-тому элементу этого массива строк, который затем копируется в i-тую строку массива word.

		for (int i = 0; i < max_word; i++) // проверка на новую строку
		{
			if (word[i][0] == '|')
			{
				position = 0;
				line++;
				continue;
			}
			position++;


			// new
			int fst{};
			for (; fst < fsts.size(); fst++)
				if (ffst::execute(fsts[fst], word[i])) //соответствует ли текущее слово лексеме, заданной конечным автоматом.
					break;

			if (strcmp(word[i], emptystr) == 0 and fst == fsts.size()) // проверка на пустое слово
				break;

			if (fst == fsts.size())
				throw ERROR_THROW_IN(5, line, position);

			switch (fsts.at(fst).lexeme) {
			case LEX_INTEGER: // same as LEX_STRING
				if (fsts[fst].type == IT::INT)
					findInt = true;
				if (fsts[fst].type == IT::STR)
					findString = true;
				break;

			case LEX_ID: {
				if (strlen(word[i]) > 7)
				{
					for (int j = strlen(word[i]) - 1; j > 5; j--) // обрезка
					{
						word[i][j] = NULL;
						sizeof(word[i])--;
					}
				}
				indxLex++;

				int idx = IT::IsId(idtable, word[i]); //существует ли индетификатор в тбл инд
				if (findFunc)
				{
					std::strcpy(oldprefix, prefix);
					std::strcpy(prefix, word[i]);
					if (!findFunc)
						findStandart = true;

				}
				else {
					if ((findBlock || findParm) && (strcmp(word[i], STANDART1) != 0 && strcmp(word[i], STANDART2) != 0))
					{
						if (!(idx != TI_NULLIDX && word[i + 1][0] == '('))     //если это не вызов функции
						{

							std::strcpy(bufprefix, prefix);
							word[i] = strcat(bufprefix, word[i]); // конкатенация префикса с текущим ид
						}
					}
				}

				idx = IT::IsId(idtable, word[i]);
				if (idx != TI_NULLIDX)
				{
					if (findNew == true)				//Проверка на повторное объявление
						throw ERROR_THROW_IN(6, line, position);

					LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line);
					LT::Add(lextable, entryLT); // созд запись в табл лексем
					continue;
				}
				else {

					if (findNew && !findInt && !findString) // если указан в коде только var
						throw ERROR_THROW_IN(4, line, position);

					if (strcmp(word[i], STANDART1) == 0 || strcmp(word[i], STANDART2) == 0 || findFunc) // если явл стандартной функцией или флаг фанк
					{
						entryIT.idxfirstLE = indxLex; // индекс первой лексемы записи
						std::strcpy(entryIT.id, word[i]); // копирует ид в запись
						if (findString || strcmp(word[i], STANDART1) == 0 || strcmp(word[i], STANDART2) == 0)
							entryIT.iddatatype = IT::STR; // установка типа
						else { entryIT.iddatatype = IT::INT; }
						entryIT.idtype = IT::F; // устанавливается тип ид как фн-ии
						entryIT.value.vstr->len = 0; //устанавливается длина строки значения записи
						std::strcpy(entryIT.value.vstr->str, emptystr); //инициализация пустой строкой

						IT::Add(idtable, entryIT); //добавление в табл ид
						idx = IT::IsId(idtable, word[i]); //получаем индекс добавленного идентификатора
						indexID++; //увеличивается индекс индетификатора

						LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line); //запись в табл лексе
						LT::Add(lextable, entryLT);

						findFunc = false;
						findInt = false; //опускаем флаги, активированные при объявлении типа возвращаемого значения функции
						findString = false;
						continue;
					}

					if (findInt || findString)
					{
						if (findParm)
						{
							entryIT.idtype = IT::P; //тип ид устанавливается как параметр, иначе переменная
						}
						else { entryIT.idtype = IT::V; }

						entryIT.idxfirstLE = indxLex;
						std::strcpy(entryIT.id, word[i]);
						if (findInt)
						{
							entryIT.iddatatype = IT::INT;
							entryIT.value.vint = 0;
						}
						else {
							entryIT.iddatatype = IT::STR;
							entryIT.value.vstr->len = 0;
							std::strcpy(entryIT.value.vstr->str, emptystr);
						}

						IT::Add(idtable, entryIT);
						int idx = IT::IsId(idtable, word[i]);
						indexID++;

						LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);


						if (findInt)findInt = false;
						else findString = false;
						findNew = false;
						continue;
					}
				}
			}

			case LEX_LITERAL: {
				if (fsts[fst].type == IT::INT) {
					indxLex++;
					_itoa_s(cLit++, charclit, sizeof(char) * 10, 10);
					std::strcpy(bufL, L);
					nameLiteral = strcat(bufL, (char*)charclit);

					int value;
					if (word[i][0] == 'O')
						value = Oct_to_dec(word[i]);
					else if (word[i][0] == 'B')
						value = Bin_to_dec(word[i]);
					else
						value = atoi((char*)word[i]);


					if (word[i - 1][0] == '-' && lextable.table[lextable.size - 1].lexema[0] != 'l' && lextable.table[lextable.size - 1].lexema[0] != 'i' && lextable.table[lextable.size - 1].lexema[0] != 'o')
						value = -value;//инвертирует знак литерала
					for (int k = 0; k < idtable.size; k++)//поиск идентичного литерала
					{
						if (idtable.table[k].idtype == IT::L and idtable.table[k].value.vint == value)
						{
							findSameID = true;
							LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
							LT::Add(lextable, entryLT);
							break;
						}
					}


					if (findSameID)
					{
						findSameID = false; continue;
					}

					entryIT.value.vint = value; //сохраняет значение литерала в записи в таблицы ид
					std::strcpy(entryIT.id, nameLiteral);
					entryIT.idxfirstLE = indxLex;
					entryIT.iddatatype = IT::INT;
					entryIT.idtype = IT::L;

					IT::Add(idtable, entryIT);
					indexID++;
					LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, idtable.size - 1, line);
					LT::Add(lextable, entryLT);


					continue;
				}
				else {
					indxLex++;

					int length = strlen(word[i]);
					for (int k = 0; k < length; k++)
						word[i][k] = word[i][k + 1]; //уст первый символ L
					word[i][length - 2] = 0; //последний нулевой


					for (int k = 0; k < idtable.size; k++) //поииск идентичного
					{
						if (strcmp(idtable.table[k].value.vstr->str, word[i]) == 0)
						{
							findSameID = true;
							LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
							LT::Add(lextable, entryLT);
							break;
						}
					}
					if (findSameID)
					{
						findSameID = false; continue;
					}

					_itoa_s(cLit++, charclit, sizeof(char) * 10, 10);
					std::strcpy(bufL, L); //копирует префикс в буфер
					nameLiteral = strcat(bufL, (char*)charclit);

					entryIT.idxfirstLE = indxLex;
					std::strcpy(entryIT.id, nameLiteral);
					entryIT.iddatatype = IT::STR;
					entryIT.idtype = IT::L;

					entryIT.value.vstr->len = length - 2;
					std::strcpy(entryIT.value.vstr->str, word[i]);
					IT::Add(idtable, entryIT);
					indexID++;

					int idx = IT::IsId(idtable, word[i]);
					LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, idtable.size - 1, line);
					LT::Add(lextable, entryLT);

					continue;
				}
			}

			case LEX_HEAD:
				findHead = true;
				cHead++;
				std::strcpy(oldprefix, prefix);
				std::strcpy(prefix, word[i]);
				break;

			case LEX_UNTIL:
				findUntil = true;
				break;

			case LEX_FUNCTION:
				findFunc = true;
				break;

			case LEX_NEW:
				findNew = true;
				break;

			case LEX_LEFTBRACE:
				findBlock = true;
				break;

			case LEX_BRACELET:
				if (!findUntil) findBlock = false;
				else findUntil = false;
				break;

			case LEX_LEFTTHESIS:
				if (idtable.table[indexID - 1].idtype == IT::F) //проверка предыдущего ид, что это функция
					findParm = true;
				break;

			case LEX_RIGHTTHESIS:
				if (findStandart) {				// если найдена стандартная функция и закрытая скобка, меняем префикс на предыдущий
					std::strcpy(prefix, oldprefix);
					findStandart = false;
				}
				findNew = false;
				findParm = false;
				break;

			case LEX_OPERATOR: {
				_itoa_s(cOperators++, charclit, sizeof(char) * 10, 10);
				std::strcpy(bufL, OP);
				nameLiteral = strcat(bufL, (char*)charclit);

				if (word[i][0] == '-' && lextable.table[lextable.size - 1].lexema[0] != 'i' && lextable.table[lextable.size - 1].lexema[0] != 'l')
					continue;
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.op == word[i][0]) //есть ли ид с таким же оператором
					{
						findSameID = true;
						LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, k, line);
						LT::Add(lextable, entryLT);
						break;
					}
				}
				if (findSameID) 	// если найден такой же стр. литерал
				{
					findSameID = false; continue;
				}
				entryIT.value.op = word[i][0]; //устанавл знач оператора а записи
				std::strcpy(entryIT.id, nameLiteral);
				entryIT.idxfirstLE = indxLex;
				entryIT.iddatatype = IT::STR;
				entryIT.idtype = IT::OP;

				IT::Add(idtable, entryIT);
				indexID++;
				LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, idtable.size - 1, line);
				entryLT.priority = 2;
				if (word[i][0] == '*' or word[i][0] == '/' or word[i][0] == '%')
					entryLT.priority = 3;
				LT::Add(lextable, entryLT);
				continue;
			}

			case LEX_RETURN:
			case LEX_PRINT:
			case LEX_SEPARATOR:
			case LEX_EQUAL:
				break;

			case LEX_COMMA:
				addLexeme(fsts[fst].lexeme, 1);
				continue;

			case LEX_COMMENT:
				continue;

			default:
				if (strcmp(word[i], emptystr) != 0)
					throw ERROR_THROW_IN(5, line, position);
				break;
			}
			addLexeme(fsts[fst].lexeme);
		}

		if (!findHead) throw ERROR_THROW(2);
		if (cHead > 1) throw ERROR_THROW(3);

		lex.lextable = lextable;
		lex.idtable = idtable;
		return lex;
	}
}

// Около 400 строки отвечает за функцию без инициализации