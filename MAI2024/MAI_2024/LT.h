#pragma once

#define LEXEMA_FIXSIZE	1			
#define LT_MAXSIZE		4096		
#define LT_TI_NULLIDX	0xfffffff	//нет элемента таблиц идентификаторов
#define LEX_INTEGER		't'	
#define LEX_STRING		't'	
#define LEX_ID			'i'	
#define LEX_LITERAL		'l'	
#define LEX_FUNCTION	'f'	
#define LEX_NEW			'v' 	
#define LEX_RETURN		'r'	
#define LEX_PRINT		'w'	
#define LEX_HEAD		'm' 	
#define LEX_SEPARATOR   ';'	
#define LEX_COMMA		','	
#define LEX_LEFTBRACE	'['	
#define LEX_BRACELET	']'	
#define LEX_LEFTTHESIS	'('	
#define LEX_RIGHTTHESIS	')'	
#define LEX_PLUS		'o'	
#define LEX_MINUS		'o'	
#define LEX_STAR		'o'	
#define LEX_DIRSLASH	'o'	
#define LEX_PROC		'o'	
#define LEX_OPERATOR	'o'	
#define LEX_EQUAL		'='
#define LEX_UNTIL		'u'
#define LEX_COMMENT		'c'

namespace LT {
	struct Entry {								//строка таблицы лексем
		char lexema[LEXEMA_FIXSIZE];			//лексема
		int sn;									//номер строки в исх. тексте
		int idxTI;								//индекс в таблице идентификаторов или LT_TI_NULLIDX
		int priority;							//приоритет оператора
	};
	struct LexTable								//экземпл€р таблицы лексем
	{
		int maxsize;							//Ємкость таблицы лексем <LT_MAXSIZE
		int size = 0;								//текущий размер таблицы лексем <maxsize
		Entry* table;							//массив строк таблицы лексем
	};

	LexTable Create(int size);					//создать таблицу лексем (Ємкость таблицы лексем <LT_MAXSIZE)
	void Add(LexTable& lextable, Entry entry);	//добавить строку в таблицу лексем
	Entry GetEntry(LexTable& lextable, int n);	//получить строку таблицы лексем
	void Delete(LexTable& lextable);			//удалить таблицу лексем
	Entry WriteEntry(Entry& entry, char lexema, int indx, int line); //запролнение строки таблицы лексем
}
