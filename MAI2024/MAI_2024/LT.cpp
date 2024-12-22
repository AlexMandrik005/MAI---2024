#include "stdafx.h"

using namespace Log;
using namespace std;

namespace LT
{
	LexTable Create(int size)
	{
		LexTable* Table = new LexTable;
		if (size > LT_MAXSIZE)
			throw ERROR_THROW(120);
		Table->maxsize = size;
		Table->size = 0;
		Table->table = new Entry[size];

		return *Table;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size + 1 > lextable.maxsize)
			throw ERROR_THROW(121);
		lextable.table[lextable.size] = entry;
		lextable.size += 1;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}

	Entry WriteEntry(Entry& entry, char lexema, int indx, int line)
	{
		entry.lexema[0] = lexema;
		entry.idxTI = indx;
		entry.sn = line;
		return entry;
	}
}