#pragma once
#include "stdafx.h"
#define PARM_IN		L"-in:"
#define	PARM_OUT	L"-out:"
#define	PARM_LOG	L"-log:"
#define	PARM_MAX_SIZE	300 //максимальный размер строк
#define	PARM_OUT_DEFAULT_EXIT	L".out"
#define	PARM_LOG_DEFAULT_EXIT	L".log"

namespace Parm
{
	struct PARM 
	{
		wchar_t in[PARM_MAX_SIZE]; 
		wchar_t out[PARM_MAX_SIZE]; 
		wchar_t log[PARM_MAX_SIZE]; 
	};
	PARM getparm(int argc, wchar_t* argv[]); //получение параметров командной строки(принимает аргументы командной строки). Возврат-структура с извлечёнными параметрами
}
