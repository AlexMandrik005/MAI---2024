#include "stdafx.h"
#include <iostream>
#include "IT.h"
#include <stack>
#include "SemanticAnalys.h"
#include "LexicalAnalys.h"
#include "LT.h"
#include "Error.h"
using namespace std;

namespace Sem
{
	void CheckParm(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable) // проверка соответствия параметров функции при её вызове.
	{
		const int max_count_parm = 9;
		stack<LT::Entry> called;
		stack<LT::Entry> buf;
		stack<LT::Entry> call;
		char calledBuf[10]; //хранение имени вызываемой функции
		for (int i = 0; i < lextable.size; i++) //проход по всему массиву лексем
		{
			if (lextable.table[i].idxTI != TI_NULLIDX && lextable.table[i].lexema[0] == LEX_ID) // если текущая лексема - идентификатор и имеет ассоциированный индекс в таблице идентификаторов.
			{
				if (idtable.table[lextable.table[i].idxTI].idtype == IT::F && lextable.table[i - 1].lexema[0] == LEX_FUNCTION) //если функция, то перед ней слово фанкшн
				{
					strcpy(calledBuf, idtable.table[lextable.table[i].idxTI].id);//копирует имя вызываемой функции
					i++; //переход к следующей лексеме после открывающей скобки
					while (lextable.table[i].lexema[0] != LEX_RIGHTTHESIS)//пока не закрывающая
					{
						if (lextable.table[i].lexema[0] == LEX_ID || lextable.table[i].lexema[0] == LEX_LITERAL) //если лексема-ид или литерал
						{
							called.push(lextable.table[i]); //помещает лексему в стек коллд, представляющий вызываемые параметры
						}
						i++;// след лексема в скобках
					}

					if (called.size() > max_count_parm)
						throw ERROR_THROW_IN(140, lextable.table[i].sn, -1);

					for (int j = i; j < lextable.size; j++) //цикл после закрывающей скобки функции
					{
						if (lextable.table[j].lexema[0] == LEX_ID && strcmp(idtable.table[lextable.table[j].idxTI].id, calledBuf) == 0) //если лексема -ид и совпад с вызыв функ
						{
							j++; //пропуск открывающей скобки
							while (lextable.table[j].lexema[0] != LEX_RIGHTTHESIS) //пока не закрывающая скобка
							{
								if (lextable.table[j].lexema[0] == LEX_ID || lextable.table[j].lexema[0] == LEX_LITERAL) //если лексема инд или литерал
									call.push(lextable.table[j]);//лексема в стек вызываемых параметров
								j++; //след лекс внутри скобок
							}

							if (call.size() > max_count_parm)
								throw ERROR_THROW_IN(140, lextable.table[j].sn, -1);

							while (!called.empty() && !call.empty()) //сравнение параметров функции и вызываемой функции(пока стеки не пусты)
							{
								if (idtable.table[called.top().idxTI].iddatatype != idtable.table[call.top().idxTI].iddatatype) //если тип параметра вызываемой функции не совпадает с типом параметра функции.
								{
									throw ERROR_THROW_IN(131, lextable.table[j].sn, -1);
								}
								buf.push(called.top()); //помещ параметр во временный стек
								called.pop(); //удаление
								call.pop();
							}

							if (called.size() != call.size()) //если размеры не совпад, то исключение
							{
								throw ERROR_THROW_IN(130, lextable.table[j].sn, -1);
							}
							else {
								while (!call.empty())//если совпадают, то стеки сбрасываются
									call.pop();
								while (!called.empty())
									called.pop();
								while (!buf.empty())//перенос из баф
								{
									called.push(buf.top());
									buf.pop();
								}
							}
						}
					}
				}
			}
		}
	}

	void CheckNativeParm(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable) // проверка соответствия параметров функции при её вызове.
	{
		const int max_count_parm = 9;
		stack<IT::IDDATATYPE> called;
		stack<LT::Entry> call;
		char calledBuf[10]; //хранение имени вызываемой функции
		for (int i = 0; i < lextable.size; i++) //проход по всему массиву лексем
		{
			bool find = false;
			if (lextable.table[i].idxTI != TI_NULLIDX && lextable.table[i].lexema[0] == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::F) // если текущая лексема - идентификатор и имеет ассоциированный индекс в таблице идентификаторов.
			{
				auto& name = idtable.table[lextable.table[i].idxTI].id;
				if (strcmp(name, STANDART1) == 0) {
					strcpy(calledBuf, idtable.table[lextable.table[i].idxTI].id);
					called.push(IT::IDDATATYPE::STR);
					called.push(IT::IDDATATYPE::STR);
					find = true;
				}

				else if (strcmp(name, STANDART2) == 0) {
					strcpy(calledBuf, idtable.table[lextable.table[i].idxTI].id);
					called.push(IT::IDDATATYPE::STR);
					called.push(IT::IDDATATYPE::STR);
					find = true;
				}

				if (called.size() > max_count_parm)
					throw ERROR_THROW_IN(140, lextable.table[i].sn, -1);
			}

			if (find) //если лексема -ид и совпад с вызыв функ
			{
				int j = i + 1;
				while (lextable.table[j].lexema[0] != LEX_RIGHTTHESIS) //пока не закрывающая скобка
				{
					if (lextable.table[j].lexema[0] == LEX_ID || lextable.table[j].lexema[0] == LEX_LITERAL) //если лексема инд или литерал
						call.push(lextable.table[j]);//лексема в стек вызываемых параметров
					j++; //след лекс внутри скобок
				}

				if (call.size() > max_count_parm)
					throw ERROR_THROW_IN(140, lextable.table[j].sn, -1);

				while (!called.empty() && !call.empty()) //сравнение параметров функции и вызываемой функции(пока стеки не пусты)
				{
					if (called.top() != idtable.table[call.top().idxTI].iddatatype) //если тип параметра вызываемой функции не совпадает с типом параметра функции.
					{
						throw ERROR_THROW_IN(131, lextable.table[j].sn, -1);
					}
					called.pop(); //удаление
					call.pop();
				}

				if (called.size() != call.size()) //если размеры не совпад, то исключение
				{
					throw ERROR_THROW_IN(130, lextable.table[j].sn, -1);
				}
				else {
					while (!call.empty())//если совпадают, то стеки сбрасываются
						call.pop();
					while (!called.empty())
						called.pop();
				}
			}
		}
	}


	void CheckReturnType(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable)
	{
		bool error = false; //была ли обнаружена ошибка
		int buf = IT::NO; bool findHead = false, findLocalFunc = false; //нахождение в объявлении головы функции и фнутри локал функции
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema[0] == LEX_HEAD)
				findHead = true;
			if (lextable.table[i].lexema[0] == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::F && lextable.table[i - 2].lexema[0] == 't')//если ид функции и перед ней тип
			{
				findLocalFunc = true; //находимся внутри локальной функции
				if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::INT)
					buf = IT::INT;
				else { buf = IT::STR; }
				continue;
			}
			if (lextable.table[i - 1].lexema[0] == LEX_RETURN)//Если предыдущая лексема - ключевое слово "return", проверяет тип возвращаемого значения.
			{
				if (findHead && !findLocalFunc) //в объявлении головы и не в локальной
					continue;
				if (idtable.table[lextable.table[i].idxTI].iddatatype != buf)//Если тип данных идентификатора не совпадает с временным буфером, генерирует ошибку.
				{
					throw ERROR_THROW_IN(132, lextable.table[i].sn, i - 1);
					error = true;
				}
				findLocalFunc = false;
			}
		}
	}


	void CheckAssignValue(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable) //проверяет согласованность типов при присваивании в программе.
	{
		bool error = false;
		stack<LT::Entry> st;
		int buf = 0; bool findFunc = false, findOperator = false;
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i - 1].lexema[0] == LEX_EQUAL && lextable.table[i - 2].lexema[0] == LEX_ID)
			{

				buf = idtable.table[lextable.table[i - 2].idxTI].iddatatype; //// запоминаем тип данных идентификатора слева от "="
				while (lextable.table[i].lexema[0] != LEX_SEPARATOR)//пока не встретим разделитель
				{
					if (lextable.table[i].lexema[0] == LEX_OPERATOR)// если оператор
						findOperator = true;
					if (lextable.table[i - 1].lexema[0] == LEX_ID && idtable.table[lextable.table[i - 1].idxTI].idtype == IT::F && lextable.table[i].lexema[0] == LEX_LEFTTHESIS) //если ид функции и после неко открыв скобка
					{
						while (lextable.table[i].lexema[0] != LEX_RIGHTTHESIS)//пропуск лексем до )
							i++;
					}
					if (lextable.table[i].lexema[0] == LEX_ID || lextable.table[i].lexema[0] == LEX_LITERAL) //если лексема - ид или литерал
						st.push(lextable.table[i]); //добавл лексему в стек
					i++; //переход к след лексеме
				}
				while (!st.empty())
				{
					if (idtable.table[st.top().idxTI].iddatatype != buf) // Если тип данных лексемы из стека не совпадает с типом данных идентификатора слева от "="
					{
						if (findOperator) //если найден оператор
						{
							throw ERROR_THROW_IN(134, lextable.table[i].sn, -1);

						}
						else {
							throw ERROR_THROW_IN(133, lextable.table[i].sn, 3);
						}
					}
					st.pop();
				}
				findOperator = false;
			}
		}
	}

	void CheckAllowedValue(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable) //проверяет допустимость значений в программе
	{
		bool findStr = false, findOp = false;
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema[0] == LEX_EQUAL)
			{
				while (lextable.table[i].lexema[0] != LEX_SEPARATOR)
				{
					if (lextable.table[i].lexema[0] == LEX_ID && idtable.table[lextable.table[i].idxTI].iddatatype == IT::STR)
						findStr = true;
					if (findStr && lextable.table[i].lexema[0] == LEX_OPERATOR && idtable.table[lextable.table[i].idxTI].value.op != '+')
						throw ERROR_THROW_IN(136, lextable.table[i].sn, -1);
					i++;
					if (lextable.table[i].lexema[0] == LEX_LITERAL && (idtable.table[lextable.table[i].idxTI].value.vint >= 2147483647 || idtable.table[lextable.table[i].idxTI].value.vint <= -2147483647))
						throw ERROR_THROW_IN(135, lextable.table[i].sn, i);
					if (lextable.table[i].lexema[0] == LEX_OPERATOR &&
						(idtable.table[lextable.table[i].idxTI].value.op == '/' || idtable.table[lextable.table[i].idxTI].value.op == '%'))
					{
						// Проверяем следующий элемент (правый операнд)
						if (lextable.table[i + 1].lexema[0] == LEX_LITERAL &&
							idtable.table[lextable.table[i + 1].idxTI].value.vint == 0)
						{
							throw ERROR_THROW_IN(139, lextable.table[i].sn, i + 1); // Ошибка: деление на ноль
						}
					}
				}
			}
			if (lextable.table[i].lexema[0] == 'i' && lextable.table[i].idxTI == TI_NULLIDX && lextable.table[i - 1].lexema[0] != 't' && lextable.table[i - 1].lexema[0] != 'f')
				throw ERROR_THROW_IN(137, lextable.table[i].sn, -1);
		}
	}

	void CheckFunc(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable)
	{
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema[0] == LEX_ID && (idtable.table[lextable.table[i].idxTI].id == STANDART1 || idtable.table[lextable.table[i].idxTI].id == STANDART2))
			{
				int j = i;
				while (j >= i - 3) // предыдущие 3 лексемы
				{
					if (lextable.table[i].lexema[0] == LEX_NEW || lextable.table[i].lexema[0] == LEX_FUNCTION || lextable.table[i].lexema[0] == 't')
						throw ERROR_THROW_IN(138, lextable.table[i].sn, -1);
					j--;
				}
			}
		}
	}

}