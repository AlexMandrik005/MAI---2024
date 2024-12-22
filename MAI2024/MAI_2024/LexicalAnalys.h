#pragma once
#include <vector>

#include "LT.h"
#include "IT.h"
#include "Log.h"
#include "In.h"
#include "ffst.h"

#define STANDART1 "joinst"
#define STANDART2 "copystr"

namespace Lex
{
	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable idtable;
	};

	LEX LexicalAnalysis(Log::LOG log, In::IN in, std::vector<ffst::FST>& fsts);
	void LTLog(LT::LexTable lt, Log::LOG log);
	void ITLog(IT::IdTable it, Log::LOG log);
};

