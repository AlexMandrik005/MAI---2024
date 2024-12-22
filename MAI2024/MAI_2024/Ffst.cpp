#include "stdafx.h"

namespace ffst
{
	RELATION::RELATION(char c, short ns)
	{
		symbol = c;
		nnode = ns;
	}

	NODE::NODE()
	{
		n_relation = NULL;
		RELATION* relations = NULL;
	};
	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	};

	/*FST::FST(const char* s, short ns, NODE n, ...)
	{
		position = -1;
		string = s;
		nstates = ns;
		nodes = new NODE[ns];

		NODE* p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];

		rstates = new short[nstates];
		memset(rstates, 0Xff, sizeof(short) * nstates);
		rstates[0] = 0;
	}*/

	FST::FST(char lexeme, IT::IDDATATYPE type, short ns, NODE n, ...)
	{
		this->lexeme = lexeme;
		this->type = type;
		position = -1;
		//string = s;
		nstates = ns; //количество состояний
		nodes = new NODE[ns]; //узлы

		NODE* p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];

		rstates = new short[nstates]; //переменное число отношений
		memset(rstates, 0Xff, sizeof(short) * nstates);
		rstates[0] = 0;
	}

	bool step(FST& fst, short*& rstates) { //Эта функция выполняет один шаг автомата поиска конечных состояний (FST).
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) {
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
		};
		return rc;
	}

	/*bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	};*/

	bool execute(FST& fst, const char* string) //Эта функция выполняет полный проход FST по входной строке.
	{
		fst.position = -1;
		fst.string = string;

		memset(fst.rstates, 0Xff, sizeof(short) * fst.nstates);
		fst.rstates[0] = 0;

		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);

		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	};
}