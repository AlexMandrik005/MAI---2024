#include "stdafx.h"
#include "LexicalAnalys.h"
#include <stack>
#include <queue>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

bool PolishNotation(int i, LT::LexTable& lextable, IT::IdTable& idtable)
{
	stack<LT::Entry> stack;		// стек дл€ операций
	queue<LT::Entry> queue;		// очередь дл€ операндов
	LT::Entry temp;
	temp.idxTI = -1;
	temp.lexema[0] = '#';
	temp.sn = -1;
	LT::Entry func;
	func.lexema[0] = '@';
	LT::Entry commas;
	int countComma = 0;			//подсчет количества зап€тых
	char* comma = new char[1] { "" };
	int countLex = 0;			// количество преобразованных лексем
	int posLex = i;				// запоминаем номер лексемы перед преобразованием
	bool findFunc = false;


	for (i; lextable.table[i].lexema[0] != LEX_SEPARATOR; i++, countLex++)
	{
		switch (lextable.table[i].lexema[0])
		{
		case LEX_ID:	// если идентификатор
		{
			queue.push(lextable.table[i]);   // помещаем в очередь
			continue;
		}
		case LEX_LITERAL:		// если литерал
		{
			queue.push(lextable.table[i]);	// помещаем в очередь
			continue;
		}
		case LEX_LEFTTHESIS:		// если (
		{
			if (i > 0 && lextable.table[i - 1].idxTI >= 0 &&
				lextable.table[i - 1].idxTI < idtable.size &&
				idtable.table[lextable.table[i - 1].idxTI].idtype == IT::F)
			{
				findFunc = true;
			}
			stack.push(lextable.table[i]); // помещаем ее в стек
			continue;
		}
		case LEX_RIGHTTHESIS:	// если )
		{
			if (findFunc)
			{
				itoa(++countComma, comma, 10); //количество зап€тых
				strcpy(commas.lexema, comma);
				stack.push(commas);
				stack.push(func);
				findFunc = false;
			}
			while (stack.top().lexema[0] != LEX_LEFTTHESIS)	// пока не встретим (
			{
				queue.push(stack.top());	// выталкиваем из стека в очередь
				stack.pop();

				if (stack.empty())
					return false;
			}
			stack.pop();	// уничтожаем (
			continue;
		}
		case LEX_OPERATOR:	// если знак оператора
		{
			while (!stack.empty() && lextable.table[i].priority <= stack.top().priority)
				// пока приоритет текущего оператора 
				//меньше или равен приоритету оператора в вершине стека
			{
				queue.push(stack.top());	// выталкиваем со стека в выходную строку
				stack.pop();
			}
			stack.push(lextable.table[i]);
			continue;
		}
		case LEX_COMMA:
		{
			countComma++;
			continue;
		}
		}
	}
	while (!stack.empty())	// если стек не пустой
	{
		if (stack.top().lexema[0] == LEX_LEFTTHESIS || stack.top().lexema[0] == LEX_RIGHTTHESIS)
			return false;
		queue.push(stack.top());	// выталкиваем все в очередь
		stack.pop();
	}
	while (countLex != 0)		// замена текущего выражени€ в таблице лексем на выражение в ѕќЋ»«
	{
		if (!queue.empty()) {
			lextable.table[posLex++] = queue.front();
			//cout << lex.idtable.table[queue.front().idxTI].id;	// вывод в консоль
			queue.pop();
		}
		else
		{
			lextable.table[posLex++] = temp;
		}
		countLex--;
	}

	for (int i = 0; i < posLex; i++)		// восстановление индексов первого вхождени€ 
		//в таблицу лексем у операторов из таблицы идентификаторов
	{
		if (lextable.table[i].lexema[0] == LEX_OPERATOR || lextable.table[i].lexema[0] == LEX_LITERAL)
			idtable.table[lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}

void WritePolishNotationToFile(const char* filename, LT::LexTable& lextable, IT::IdTable& idtable) {
	std::ofstream outfile(filename);
	if (!outfile.is_open()) {
		std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
		return;
	}

	for (int i = 0; i < lextable.size; ++i) {
		if (lextable.table[i].lexema[0] == LEX_SEPARATOR) {
			// ѕропускаем разделители
			continue;
		}

		std::queue<LT::Entry> queue;   // ќчередь дл€ операндов
		std::stack<LT::Entry> stack;   // —тек дл€ операций
		bool findFunc = false;
		int countComma = 0;

		for (; lextable.table[i].lexema[0] != LEX_SEPARATOR && i < lextable.size; ++i) {
			switch (lextable.table[i].lexema[0]) {
			case LEX_ID: {
				queue.push(lextable.table[i]);
				break;
			}
			case LEX_LITERAL: {
				queue.push(lextable.table[i]);
				break;
			}
			case LEX_LEFTTHESIS: {
				if (i > 0 && lextable.table[i - 1].idxTI >= 0 &&
					lextable.table[i - 1].idxTI < idtable.size &&
					idtable.table[lextable.table[i - 1].idxTI].idtype == IT::F) {
					findFunc = true;
				}
				stack.push(lextable.table[i]);
				break;
			}
			case LEX_RIGHTTHESIS: {
				if (findFunc) {
					LT::Entry commas;
					LT::Entry func;
					func.lexema[0] = '@';

					char comma[10];
					snprintf(comma, sizeof(comma), "%d", ++countComma);
					strcpy(commas.lexema, comma);

					stack.push(commas);
					stack.push(func);
					findFunc = false;
				}
				while (!stack.empty() && stack.top().lexema[0] != LEX_LEFTTHESIS) {
					queue.push(stack.top());
					stack.pop();
				}
				if (!stack.empty()) stack.pop(); // ”дал€ем '('
				break;
			}
			case LEX_OPERATOR: {
				while (!stack.empty() && lextable.table[i].priority <= stack.top().priority) {
					queue.push(stack.top());
					stack.pop();
				}
				stack.push(lextable.table[i]);
				break;
			}
			case LEX_COMMA: {
				countComma++;
				break;
			}
			}
		}

		while (!stack.empty()) {
			if (stack.top().lexema[0] == LEX_LEFTTHESIS || stack.top().lexema[0] == LEX_RIGHTTHESIS) {
				outfile.close();
				return;
			}
			queue.push(stack.top());
			stack.pop();
		}

		while (!queue.empty()) {
			LT::Entry entry = queue.front();
			queue.pop();

			if (entry.idxTI >= 0 && entry.idxTI < idtable.size) {
				outfile << idtable.table[entry.idxTI].id << ' ';
			}
			else {
				outfile << entry.lexema << ' ';
			}
		}

		outfile << std::endl; // «аканчиваем запись одной строки ѕќЋ»«
	}

	outfile.close();
}

