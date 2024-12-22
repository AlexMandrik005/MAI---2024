#pragma once
#define ID_MAXSIZE		15				//максимальное количество символов в идентификаторе
#define TI_MAXSIZE		4096			//максимальное количество строк в таблице идентификатора
#define TI_INT_DEFAULT  0x00000000		//значение по умолчанию для integer
#define TI_STR_DEFAULT  0x00			//значение по умолчанию для string
#define TI_NULLIDX		0xffffffff		//нет элемента таблицы идентификатора
#define TI_STR_MAXSIZE  255

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2, NO = 0 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, OP = 5 };	 //типы идентификаторов: переменная, функция, параметр, литерал

	struct Entry			//строка таблицы идентификаторов
	{
		int idxfirstLE;					//индекс первой строки в таблице лексем
		char id[ID_MAXSIZE];			//идентификатор
		IDDATATYPE iddatatype;			//тип данных
		IDTYPE idtype;					//тип идентификатора
		union
		{

			char op;					//значение оператора
			int vint;					//значение int
			struct
			{
				int len;						//количество символов в string
				char str[TI_STR_MAXSIZE - 1];   //символы строки
			} vstr[TI_STR_MAXSIZE];				//значение строки
		}value;		//значение идентификатора
	};

	struct IdTable			//экземпляр таблицы идентификатора
	{
		int maxsize;		//ёмкость таблицы идентификатора
		int size;			//текущий размер таблицы идентификаторов
		Entry* table;		//строка таблицы идентификаторов
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);
	void Delete(IdTable& idtable);
};

