#include "Split.h"

char** SplitText(char source[], int size)
{
	char** word = new char* [max_word];
	for (int i = 0; i < max_word; i++)
		word[i] = new char[size_word] {NULL};

	char punct_sym[] = ";[](){}%+-*=/|, ";
	bool findLit = false;
	bool findComm = false;

	int k = 0;
	for (int i = 0; i < max_word; i++)
	{
		if (k > size) break;
		for (int j = 0; j < size_word; j++)// Внутренний цикл перебирает символы внутри текущего слова
		{
			if (source[k] == '\'')
			{
				if (!findLit)// Обработка литералов
				{
					findLit = true;
					word[i][j] = source[k];
					k++;
					continue;
				}
				else
				{
					findLit = false;
					word[i][j] = source[k];
					word[i][++j] = '\0';
					k++; break;
				}
			}
			if (source[k] == '#')// Обработка комментариев
			{
				if (!findLit)
					findComm = true;
				word[i][j] = source[k];
				k++;
				continue;
			}
			if (source[k] == ';' && findComm == true)
			{ // Конец комментария
				findComm = false;
				word[i][j] = source[k];
				word[i][++j] = '\0';
				k++; break;
			}
			if (strchr(punct_sym, source[k]) != 0)
			{
				// Обработка знаков пунктуации
				if (source[k] == '|') { word[i][j] = source[k]; k++; break; }
				if (source[k] == ' ')
				{
					if (findLit || findComm)
					{
						word[i][j] = source[k];
						k++; continue;
					}
					k++; i--; break;
				}

				word[i][j] = source[k];
				word[i][++j] = '\0';
				k++;  break;
			}
			if (source[k] == '\n')
			{
				k++; i--; break;
			}

			word[i][j] = source[k];
			k++;
			if ((strchr(punct_sym, source[k]) != 0) && (!findLit) && (!findComm))// Если следующий символ - знак пунктуации, и не находимся в литерале или комментарии,
				// то завершаем текущее слово
			{
				word[i][++j] = '\0';
				break;
			}
		}
	}
	return word;
}


