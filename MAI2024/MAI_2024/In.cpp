#include "stdafx.h"
#include "In.h"
#include "Error.h"

using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in;
		in.size = 0;
		in.lines = 0;
		in.ignor = 0;
		int col = 0;

		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];

		ifstream fin(infile);
		if (fin.fail()) throw ERROR_THROW(110);

		while (in.size < IN_MAX_LEN_TEXT)
		{
			char c; fin.get(c);
			unsigned char x = c;

			if (fin.eof())
			{
				text[in.size] = '\0';
				in.lines++;
				break;
			}

			if (x == IN_CODE_ENDL)
			{
				text[in.size] = '|';
				text[++in.size] = x;
				in.size++;
				in.lines++;
				col = 0;
				continue;
			}


			if (in.code[x] == in.T)
			{
				if (x == ' ')
				{
					if ((text[in.size - 1] != '+') && (text[in.size - 1] != '-') && (text[in.size - 1] != '=') &&
						(text[in.size - 1] != '*') && (text[in.size - 1] != '/') &&
						(text[in.size - 1] != ' ') && (text[in.size - 1] != '\n'))
					{
						text[in.size] = x;
						in.size++;
					}
					continue;
				}

				if ((x == '+') || (x == '-') || (x == '*') || (x == '/') || (x == '='))
				{
					if (text[in.size - 1] != ' ')
					{
						text[in.size] = x;
						in.size++;
					}
					else text[in.size - 1] = x;
					continue;
				}

				text[in.size] = x;
				in.size++;
				col++;
			}
			else if (in.code[x] == in.I)
			{
				in.ignor++;
			}
			else if (in.code[x] == in.F)
			{
				throw ERROR_THROW_IN(111, in.lines, col);
			}
			else
			{
				text[in.size] = in.code[x];
				in.size++;
				col++;
			}

		}
		in.text = text;
		return in;
	}
}