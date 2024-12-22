#pragma once
#include "Parm.h"
#include "Error.h"
#include "In.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE]; // Путь к лог-файлу
		std::ofstream* stream;  // Указатель на поток вывода
	};

	static const LOG INITLOG = { L"", NULL };// Константа INITLOG - инициализированная структура LOG
	LOG getlog(wchar_t logfile[]);// Функция для получения экземпляра структуры LOG с указанным путем к лог-файлу(Инициализация константы INITLOG структурой LOG с пустым путем к лог-файлу и нулевым указателем на поток.)
	// Функции для записи строк в лог - файл с переменным числом аргументов
	void WriteLine(LOG log, const char* c, ...); //записывает строки с переменным числом аргументов в лог-файл.
	void WriteLine(LOG log, const wchar_t* c, ...);
	// Функции для записи информации в лог-файл(логирование, параметры, входные данные, ошибки).
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteError(LOG log, Error::ERROR error);

	void Close(LOG log);
};
