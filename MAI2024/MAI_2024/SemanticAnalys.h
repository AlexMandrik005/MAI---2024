#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include "Log.h"

namespace Sem
{
	void CheckNativeParm(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable);				//проверка параметров нативных функции на совпадение по типу и количеству
	void CheckParm(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable);					//проверка параметров функции на совпадение по типу и количеству
	void CheckReturnType(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable);				//преверка совпадения типа функции и типа возвращаемого значения
	void CheckAssignValue(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable);			//проверка соответствия типа переменной и присваиваемого значения
	void CheckAllowedValue(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable);			//проверка присваиваемых числовых значений на допустимость
	void CheckFunc(Log::LOG log, LT::LexTable lextable, IT::IdTable idtable);
}
