#include "Error.h"
#include <iostream>

namespace Error
{
	ERROR error[ERROR_MAX_ENTRY] =
	{ 
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY(2, "Sem: отсутствует точка входа chief"),
		ERROR_ENTRY(3, "Sem: допустима только 1 точка входа chief"),
		ERROR_ENTRY(4, "Sem: переменная или функция должны иметь определенный тип данных"),
		ERROR_ENTRY(5, "Lex: лексема не распознана"),
		ERROR_ENTRY(6, "Sem: повторное объявление переменной запрещено"),ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Lex: превышен размер таблицы лексем"),
		ERROR_ENTRY(121, "Lex: таблица лексем переполнена"),
		ERROR_ENTRY(122, "Lex: превышен размер таблицы идентификаторов"),
		ERROR_ENTRY(123, "Lex: таблица идентификаторов переполнена"),
		ERROR_ENTRY_NODEF(124), ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126),
		ERROR_ENTRY_NODEF(127),	ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "Sem: количество параметров функции не совпадает."),
		ERROR_ENTRY(131, "Sem: типы формальных и фактических параметров функции не совпадают."),
		ERROR_ENTRY(132,"Sem: тип функции и тип возвращаемого значения не совпадают."),
		ERROR_ENTRY(133, "Sem: недопустимый тип присваиваемого значения"),
		ERROR_ENTRY(134,"Sem: операции над аргументами разных типов недопустимы."),
		ERROR_ENTRY(135,"Sem: число выходит за границы допустимого диапазона."),
		ERROR_ENTRY(136,"Sem: недопустимые операции со строками."),
		ERROR_ENTRY(137,"Sem: идентификатор не может быть использован до его объявления"),
		ERROR_ENTRY(138, "Sem: стандартные функции не требуют объявления."),
		ERROR_ENTRY(139, "Sem: Деление на ноль."),
		ERROR_ENTRY(140, "Sem: много параметров. Разрешено только 9 "),
		ERROR_ENTRY_NODEF(141),
		ERROR_ENTRY_NODEF(142),
		ERROR_ENTRY_NODEF(143),
		ERROR_ENTRY_NODEF(144),
		ERROR_ENTRY_NODEF(145),
		ERROR_ENTRY_NODEF(146),
		ERROR_ENTRY_NODEF(147),
		ERROR_ENTRY_NODEF(148),
		ERROR_ENTRY_NODEF(149),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Syn: неверная структура программы"),
		ERROR_ENTRY(601, "Syn: неверная конструкция в функции"),
		ERROR_ENTRY(602, "Syn: ошибка в выражении"),
		ERROR_ENTRY(603, "Syn: ошибка в параметрах функции"),
		ERROR_ENTRY(604, "Syn: ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(605),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),
		ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF(660),
		ERROR_ENTRY_NODEF(661),ERROR_ENTRY_NODEF(662),ERROR_ENTRY_NODEF(663),ERROR_ENTRY_NODEF(664),ERROR_ENTRY_NODEF(665),
		ERROR_ENTRY(666, "Ошибка синтаксического анализа"),
		ERROR_ENTRY_NODEF(667),ERROR_ENTRY_NODEF(668),ERROR_ENTRY_NODEF(669),
		ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900),
	};

	ERROR geterror(int id)
	{
		ERROR newError;
		if (id<0 || id>ERROR_MAX_ENTRY) newError.id = 0;
		else newError.id = id;
		for (int i = 0; i < ERROR_MAXSIZE_MESSAGE; i++)
			newError.message[i] = error[newError.id].message[i];

		return newError;
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR newError = geterror(id);
		newError.inext.col = col;
		newError.inext.line = line;
		return newError;
	}
};