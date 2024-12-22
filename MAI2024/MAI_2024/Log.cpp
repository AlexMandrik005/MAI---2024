#include "stdafx.h"	
#include "Log.h"	
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

namespace Log
{
	LOG getlog(wchar_t logfile[])// Функция getlog для создания структуры LOG и открытия файла лога
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile);
		if (log.stream->fail())
			throw ERROR_THROW(112);
		wcscpy_s(log.logfile, logfile);
		return log;
	}
	void WriteLine(LOG log, const char* c, ...) // Функция WriteLine для записи строки в файл лога (с переменным числом аргументов)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "")
			*log.stream << ptr[i++];
		*log.stream << endl;
	}
	void WriteLine(LOG log, const wchar_t* c, ...) // Функция WriteLine для записи строки в файл лога (с переменным числом аргументов)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")// Перебор элементов массива указателей до пустой строки (завершающей нулевой символ)
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << endl;
	}
	void WriteLog(LOG log) // Функция WriteLog для записи времени и даты в файл лога
	{
		tm* timeinf;
		time_t timet;
		time(&timet);
		timeinf = localtime(&timet);
		char temp[100];
		strftime(temp, sizeof(temp), "\n------------ПРОТОКОЛ------------\n ----%d.%m.%y %T----\n ", timeinf);
		*log.stream << temp;
	}
	void WriteIn(LOG log, In::IN in)// Функция WriteIn для записи информации из структуры In::IN в файл лога (принимает структуру LOG и структуру In::IN в качестве аргументов.)
	{
		*log.stream << "\n---- Исходные данные ----\n" << in.text
			<< "\n\nВсего символов: " << in.size
			<< "\n\nВсего строк: " << in.lines << endl;
		//<< "\n\nПропущено: " << in.ignor << endl;
	}
	void WriteParm(LOG log, Parm::PARM parm) // Функция WriteParm для записи информации из структуры Parm::PARM в файл лога
	{

		char in_text[PARM_MAX_SIZE];
		char out_text[PARM_MAX_SIZE];
		char log_text[PARM_MAX_SIZE];

		wcstombs(in_text, parm.in, PARM_MAX_SIZE);
		wcstombs(out_text, parm.out, PARM_MAX_SIZE);
		wcstombs(log_text, parm.log, PARM_MAX_SIZE);

		*log.stream << "\n ---- Параметры ---- \n\n-in: " << in_text
			<< "\n-out: " << out_text
			<< "\n-log: " << log_text << endl;
	}
	void WriteError(LOG log, Error::ERROR error) // Функция WriteError для записи информации из структуры Error::ERROR в файл лога
	{
		if (log.stream)
		{
			*log.stream << "\nОшибка " << error.id
				<< ": " << error.message
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << endl;
			Close(log);
			cout << "\nОшибка " << error.id
				<< ": " << error.message
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << endl;
		}
		else
		{
			cout << "\nОшибка " << error.id
				<< ": " << error.message
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << endl;
		}
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
	}
}