#pragma once
#include "stdafx.h"
#include "LexicalAnalys.h"
bool PolishNotation(int i, LT::LexTable& lextable, IT::IdTable& idtable);
void PolishStart(Lex::LEX lex);
void WritePolishNotationToFile(const char* filename, LT::LexTable& lextable, IT::IdTable& idtable);