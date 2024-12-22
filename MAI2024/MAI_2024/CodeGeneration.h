#pragma once
#include <iostream>
#include "IT.h"
#include "LT.h"
#include "Log.h"
#include <vector>
#define BEFORE_DATA_SECTIONS_ENTRY ".586\n.model flat, stdcall\nincludelib D:\\Visual_Lab_3sem\\Course_Project_MAI_2024\\MAI2024\\Debug\\StandartLib.lib\nincludelib kernel32.lib\nincludelib libucrt.lib"
#define CSMAXSIZE 255


namespace CG
{
	enum INSTRUCTIONTYPE
	{// типы инструкций
		PUSH = 0,		// отправка переменной с стек
		FUNC = 2,		// инициализация функции tfi
		RET = 3,		// возврат значения функции: return l/i/expression;
		PRNT = 4,		// вывод : print  l/i/expression;
		ADD = 5,		// +
		ADDSTR = 6,
		DIFF = 7,		// - бинарный
		DIV = 9,		// /
		MOD = 10,			// % - остаток от деления
		MUL = 11,		// *
		SEP = 12,		// ;
		PARM = 13,		//  параметр: (ti,...)
		CALL = 14,		// вызов функции : i(...)
		ENDP = 15,		//конец процедуры: fucn_name ENDP
		UNTIL1 = 16,
		UNTIL2 = 17
	};

	struct ConstSegment
	{
		char** Data;
		int size;
		int maxSize;
		ConstSegment(int _size)
		{
			size = 0;
			maxSize = _size + 4;
			Data = new char* [maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			Data[size++] = (char*)BEFORE_DATA_SECTIONS_ENTRY;
			Data[size++] = (char*)"\n\nExitProcess PROTO : DWORD\ncopystr PROTO : DWORD, : DWORD\njoinst PROTO : DWORD, : DWORD\noutstr PROTO : DWORD\noutint PROTO : SDWORD ";
			Data[size++] = (char*)"\n.stack 4096\n.const";
			Data[size++] = (char*)"\n\toverflow db 'ERROR: VARIABLE OVERFLOW', 0 \n\tnull_division db 'ERROR: DIVISION BY ZERO', 0";

		}
	};
	struct DataSegment
	{
		char** Data;
		int size;
		int maxSize;
		DataSegment(int _size)
		{
			size = 0;
			maxSize = _size + 1;
			Data = new char* [maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			Data[size++] = (char*)"\n.data";
		}
	};
	struct CodeSegment
	{
		char** Data;
		int size;
		int maxSize;
		void add(std::string str);
		CodeSegment()
		{
			size = 0;
			maxSize = CSMAXSIZE;
			Data = new char* [maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			Data[size++] = (char*)"\n.code";
		}
	};
	void add(IT::IdTable& idtable, ConstSegment& cnst);
	void add(IT::IdTable& idtable, DataSegment& dataseg);
	void generateExpression(std::vector<LT::Entry>& tempEntries, CodeSegment& CS, int idxTI, IT::IdTable iT, int type = IT::INT);
	void CodeSegmentGeneration(CodeSegment& CS, LT::LexTable l, IT::IdTable& iT);
	std::string	generateInstructions(INSTRUCTIONTYPE t, int idxTI, IT::IdTable iT, int type = IT::INT, std::string fucn_name = "");
	void endOfFucntion(CodeSegment& CS);
	void startGeneration(const char* file, ConstSegment& CnstS, DataSegment& DS, CodeSegment& CS);

	void print(Log::LOG log, ConstSegment& cnst, DataSegment& dataseg, CodeSegment& codeseg);

}

