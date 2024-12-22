#pragma once


// TOKEN_NAME, DATATYPE, size, nodes
#define FST_NEW LEX_NEW, IT::NO, 4,	\
	ffst::NODE(1, ffst::RELATION('v', 1)),\
	ffst::NODE(1, ffst::RELATION('a', 2)),\
	ffst::NODE(1, ffst::RELATION('r', 3)),\
	ffst::NODE()

#define FST_UNTIL LEX_UNTIL, IT::NO, 6,    \
	ffst::NODE(1, ffst::RELATION('u', 1)),\
	ffst::NODE(1, ffst::RELATION('n', 2)),\
	ffst::NODE(1, ffst::RELATION('t', 3)),\
	ffst::NODE(1, ffst::RELATION('i', 4)),\
	ffst::NODE(1, ffst::RELATION('l', 5)),\
	ffst::NODE()


#define FST_INTEGER LEX_INTEGER, IT::INT, 4,	\
	ffst::NODE(1, ffst::RELATION('i', 1)),\
	ffst::NODE(1, ffst::RELATION('n', 2)),\
	ffst::NODE(1, ffst::RELATION('t', 3)),\
	ffst::NODE()

#define FST_STRING LEX_STRING, IT::STR, 7,	\
	ffst::NODE(1, ffst::RELATION('s', 1)),\
	ffst::NODE(1, ffst::RELATION('t', 2)),\
	ffst::NODE(1, ffst::RELATION('r', 3)),\
	ffst::NODE(1, ffst::RELATION('i', 4)),\
	ffst::NODE(1, ffst::RELATION('n', 5)),\
	ffst::NODE(1, ffst::RELATION('g', 6)),\
	ffst::NODE()

#define FST_FUNCTION LEX_FUNCTION, IT::NO, 3,	\
	ffst::NODE(1, ffst::RELATION('f', 1)),\
	ffst::NODE(1, ffst::RELATION('n', 2)),\
	ffst::NODE()

#define FST_RETURN LEX_RETURN, IT::NO, 6,	\
	ffst::NODE(1, ffst::RELATION('r', 1)),\
	ffst::NODE(1, ffst::RELATION('e', 2)),\
	ffst::NODE(1, ffst::RELATION('o', 3)),\
	ffst::NODE(1, ffst::RELATION('u', 4)),\
	ffst::NODE(1, ffst::RELATION('t', 5)),\
	ffst::NODE()

#define FST_PRINT LEX_PRINT, IT::NO, 6,	\
	ffst::NODE(1, ffst::RELATION('w', 1)),\
	ffst::NODE(1, ffst::RELATION('r', 2)),\
	ffst::NODE(1, ffst::RELATION('i', 3)),\
	ffst::NODE(1, ffst::RELATION('t', 4)),\
	ffst::NODE(1, ffst::RELATION('e', 5)),\
	ffst::NODE()


#define FST_HEAD LEX_HEAD, IT::NO, 6,	\
	ffst::NODE(1, ffst::RELATION('c', 1)),\
	ffst::NODE(1, ffst::RELATION('h', 2)),\
	ffst::NODE(1, ffst::RELATION('i', 3)),\
	ffst::NODE(1, ffst::RELATION('e', 4)),\
	ffst::NODE(1, ffst::RELATION('f', 5)),\
	ffst::NODE()

#define FST_OCT  LEX_LITERAL, IT::INT, 4,\
	ffst::NODE(1, ffst::RELATION('O', 1)),\
	ffst::NODE(1, ffst::RELATION('x', 2)),\
	ffst::NODE(16, ffst::RELATION('0', 2),ffst::RELATION('1', 2), ffst::RELATION('2', 2), ffst::RELATION('3', 2),\
				  ffst::RELATION('4', 2), ffst::RELATION('5', 2),ffst::RELATION('6', 2), ffst::RELATION('7', 2),\
				  ffst::RELATION('0', 3), ffst::RELATION('1', 3), ffst::RELATION('2', 3),ffst:: RELATION('3', 3),\
				  ffst::RELATION('4', 3), ffst::RELATION('5', 3), ffst::RELATION('6', 3), ffst::RELATION('7', 3)),\
	ffst::NODE()

#define FST_BIN  LEX_LITERAL, IT::INT, 4,\
	ffst::NODE(1, ffst::RELATION('B', 1)),\
	ffst::NODE(1, ffst::RELATION('x', 2)),\
	ffst::NODE(4, ffst::RELATION('0', 2),ffst::RELATION('1', 2),\
				  ffst::RELATION('0', 3), ffst::RELATION('1', 3)),\
	ffst::NODE()



#define FST_ID LEX_ID, IT::NO, 2,	\
	ffst::NODE(104,	\
	ffst::RELATION('A', 0), ffst::RELATION('B', 0), ffst::RELATION('C', 0), ffst::RELATION('D', 0), ffst::RELATION('E', 0), ffst::RELATION('F', 0),\
	ffst::RELATION('G', 0), ffst::RELATION('H', 0), ffst::RELATION('I', 0), ffst::RELATION('J', 0), ffst::RELATION('K', 0), ffst::RELATION('L', 0),\
	ffst::RELATION('M', 0), ffst::RELATION('N', 0), ffst::RELATION('O', 0), ffst::RELATION('P', 0), ffst::RELATION('Q', 0), ffst::RELATION('R', 0),\
	ffst::RELATION('S', 0), ffst::RELATION('T', 0), ffst::RELATION('U', 0), ffst::RELATION('V', 0), ffst::RELATION('W', 0), ffst::RELATION('X', 0),\
	ffst::RELATION('Y', 0), ffst::RELATION('Z', 0),\
	\
	ffst::RELATION('a', 0), ffst::RELATION('b', 0), ffst::RELATION('c', 0), ffst::RELATION('d', 0), ffst::RELATION('e', 0), ffst::RELATION('f', 0),\
	ffst::RELATION('g', 0), ffst::RELATION('h', 0), ffst::RELATION('i', 0), ffst::RELATION('j', 0), ffst::RELATION('k', 0), ffst::RELATION('l', 0),\
	ffst::RELATION('m', 0), ffst::RELATION('n', 0), ffst::RELATION('o', 0), ffst::RELATION('p', 0), ffst::RELATION('q', 0), ffst::RELATION('r', 0),\
	ffst::RELATION('s', 0), ffst::RELATION('t', 0), ffst::RELATION('u', 0), ffst::RELATION('v', 0), ffst::RELATION('w', 0), ffst::RELATION('x', 0),\
	ffst::RELATION('y', 0), ffst::RELATION('z', 0),\
	\
	ffst::RELATION('A', 0), ffst::RELATION('B', 0), ffst::RELATION('C', 0), ffst::RELATION('D', 0), ffst::RELATION('E', 0), ffst::RELATION('F', 0),\
	ffst::RELATION('G', 0), ffst::RELATION('H', 0), ffst::RELATION('I', 0), ffst::RELATION('J', 0), ffst::RELATION('K', 0), ffst::RELATION('L', 0),\
	ffst::RELATION('M', 0), ffst::RELATION('N', 0), ffst::RELATION('O', 0), ffst::RELATION('P', 0), ffst::RELATION('Q', 0), ffst::RELATION('R', 0),\
	ffst::RELATION('S', 0), ffst::RELATION('T', 0), ffst::RELATION('U', 0), ffst::RELATION('V', 0), ffst::RELATION('W', 0), ffst::RELATION('X', 0),\
	ffst::RELATION('Y', 0), ffst::RELATION('Z', 0),\
	\
	ffst::RELATION('a', 1), ffst::RELATION('b', 1), ffst::RELATION('c', 1), ffst::RELATION('d', 1), ffst::RELATION('e', 1), ffst::RELATION('f', 1),\
	ffst::RELATION('g', 1), ffst::RELATION('h', 1), ffst::RELATION('i', 1), ffst::RELATION('j', 1), ffst::RELATION('k', 1), ffst::RELATION('l', 1),\
	ffst::RELATION('m', 1), ffst::RELATION('n', 1), ffst::RELATION('o', 1), ffst::RELATION('p', 1), ffst::RELATION('q', 1), ffst::RELATION('r', 1),\
	ffst::RELATION('s', 1), ffst::RELATION('t', 1), ffst::RELATION('u', 1), ffst::RELATION('v', 1), ffst::RELATION('w', 1), ffst::RELATION('x', 1),\
	ffst::RELATION('y', 1), ffst::RELATION('z', 1)),\
	ffst::NODE()

#define FST_INTLIT LEX_LITERAL, IT::INT, 3,	\
	ffst::NODE(19,	\
	ffst::RELATION('1', 1), ffst::RELATION('2', 1), ffst::RELATION('3', 1), ffst::RELATION('4', 1), ffst::RELATION('5', 1), ffst::RELATION('6', 1),\
	ffst::RELATION('7', 1), ffst::RELATION('8', 1), ffst::RELATION('9', 1),\
	ffst::RELATION('1', 2), ffst::RELATION('2', 2), ffst::RELATION('3', 2), ffst::RELATION('4', 2), ffst::RELATION('5', 2), ffst::RELATION('6', 2),\
	ffst::RELATION('7', 2), ffst::RELATION('8', 2), ffst::RELATION('9', 2), ffst::RELATION('0', 2)),\
	ffst::NODE(20,\
	ffst::RELATION('1', 1), ffst::RELATION('2', 1), ffst::RELATION('3', 1), ffst::RELATION('4', 1), ffst::RELATION('5', 1), ffst::RELATION('6', 1),\
	ffst::RELATION('7', 1), ffst::RELATION('8', 1), ffst::RELATION('9', 1), ffst::RELATION('0', 1),\
	ffst::RELATION('1', 2), ffst::RELATION('2', 2), ffst::RELATION('3', 2), ffst::RELATION('4', 2), ffst::RELATION('5', 2), ffst::RELATION('6', 2),\
	ffst::RELATION('7', 2), ffst::RELATION('8', 2), ffst::RELATION('9', 2), ffst::RELATION('0', 2)),\
	ffst::NODE()

#define FST_STRLIT LEX_LITERAL, IT::STR, 4,	\
	ffst::NODE(2, ffst::RELATION('\'', 1), ffst::RELATION('\'', 2)),\
	ffst::NODE(158,	\
	ffst::RELATION('a', 1), ffst::RELATION('b', 1), ffst::RELATION('c', 1), ffst::RELATION('d', 1), ffst::RELATION('e', 1), ffst::RELATION('f', 1),\
	ffst::RELATION('g', 1), ffst::RELATION('h', 1), ffst::RELATION('i', 1), ffst::RELATION('j', 1), ffst::RELATION('k', 1), ffst::RELATION('l', 1),\
	ffst::RELATION('m', 1), ffst::RELATION('n', 1), ffst::RELATION('o', 1), ffst::RELATION('p', 1), ffst::RELATION('q', 1), ffst::RELATION('r', 1),\
	ffst::RELATION('s', 1), ffst::RELATION('t', 1), ffst::RELATION('u', 1), ffst::RELATION('v', 1), ffst::RELATION('w', 1), ffst::RELATION('x', 1),\
	ffst::RELATION('y', 1), ffst::RELATION('z', 1), ffst::RELATION('1', 1), ffst::RELATION('2', 1), ffst::RELATION('3', 1), ffst::RELATION('4', 1),\
	ffst::RELATION('5', 1), ffst::RELATION('6', 1), ffst::RELATION('7', 1), ffst::RELATION('8', 1), ffst::RELATION('9', 1), ffst::RELATION('0', 1),\
	\
	ffst::RELATION('à', 1), ffst::RELATION('á', 1), ffst::RELATION('â', 1), ffst::RELATION('ã', 1), ffst::RELATION('ä', 1), ffst::RELATION('å', 1),\
	ffst::RELATION('¸', 1), ffst::RELATION('æ', 1), ffst::RELATION('ç', 1), ffst::RELATION('è', 1), ffst::RELATION('é', 1), ffst::RELATION('ê', 1),\
	ffst::RELATION('ë', 1), ffst::RELATION('ì', 1), ffst::RELATION('í', 1), ffst::RELATION('î', 1), ffst::RELATION('ï', 1), ffst::RELATION('ð', 1),\
	ffst::RELATION('ñ', 1), ffst::RELATION('ò', 1), ffst::RELATION('ó', 1), ffst::RELATION('ô', 1), ffst::RELATION('õ', 1), ffst::RELATION('ö', 1),\
	ffst::RELATION('÷', 1), ffst::RELATION('ø', 1), ffst::RELATION('ù', 1), ffst::RELATION('ú', 1), ffst::RELATION('û', 1), ffst::RELATION('ü', 1),\
	ffst::RELATION('ý', 1), ffst::RELATION('þ', 1), ffst::RELATION('ÿ', 1), ffst::RELATION(' ', 1), ffst::RELATION('.', 1), ffst::RELATION(',', 1),\
	ffst::RELATION('?', 1), ffst::RELATION('!', 1), ffst::RELATION(';', 1), ffst::RELATION(':', 1), ffst::RELATION('-', 1), ffst::RELATION(')', 1),\
	ffst::RELATION('(', 1), \
	\
	ffst::RELATION('a', 2), ffst::RELATION('b', 2), ffst::RELATION('c', 2), ffst::RELATION('d', 2), ffst::RELATION('e', 2), ffst::RELATION('f', 2),\
	ffst::RELATION('g', 2), ffst::RELATION('h', 2), ffst::RELATION('i', 2), ffst::RELATION('j', 2), ffst::RELATION('k', 2), ffst::RELATION('l', 2),\
	ffst::RELATION('m', 2), ffst::RELATION('n', 2), ffst::RELATION('o', 2), ffst::RELATION('p', 2), ffst::RELATION('q', 2), ffst::RELATION('r', 2),\
	ffst::RELATION('s', 2), ffst::RELATION('t', 2), ffst::RELATION('u', 2), ffst::RELATION('v', 2), ffst::RELATION('w', 2), ffst::RELATION('x', 2),\
	ffst::RELATION('y', 2), ffst::RELATION('z', 2), ffst::RELATION('1', 2), ffst::RELATION('2', 2), ffst::RELATION('3', 2), ffst::RELATION('4', 2),\
	ffst::RELATION('5', 2), ffst::RELATION('6', 2), ffst::RELATION('7', 2), ffst::RELATION('8', 2), ffst::RELATION('9', 2), ffst::RELATION('0', 2),\
	\
	ffst::RELATION('à', 2), ffst::RELATION('á', 2), ffst::RELATION('â', 2), ffst::RELATION('ã', 2), ffst::RELATION('ä', 2), ffst::RELATION('å', 2),\
	ffst::RELATION('¸', 2), ffst::RELATION('æ', 2), ffst::RELATION('ç', 2), ffst::RELATION('è', 2), ffst::RELATION('é', 2), ffst::RELATION('ê', 2),\
	ffst::RELATION('ë', 2), ffst::RELATION('ì', 2), ffst::RELATION('í', 2), ffst::RELATION('î', 2), ffst::RELATION('ï', 2), ffst::RELATION('ð', 2),\
	ffst::RELATION('ñ', 2), ffst::RELATION('ò', 2), ffst::RELATION('ó', 2), ffst::RELATION('ô', 2), ffst::RELATION('õ', 2), ffst::RELATION('ö', 2),\
	ffst::RELATION('÷', 2), ffst::RELATION('ø', 2), ffst::RELATION('ù', 2), ffst::RELATION('ú', 2), ffst::RELATION('û', 2), ffst::RELATION('ü', 2),\
	ffst::RELATION('ý', 2), ffst::RELATION('þ', 2), ffst::RELATION('ÿ', 2), ffst::RELATION(' ', 2), ffst::RELATION('.', 2), ffst::RELATION(',', 2),\
	ffst::RELATION('?', 2), ffst::RELATION('!', 2), ffst::RELATION(';', 2), ffst::RELATION(':', 2), ffst::RELATION('-', 2), ffst::RELATION(')', 2),\
	ffst::RELATION('(', 2)),\
	\
	ffst::NODE(1, ffst::RELATION('\'', 3)),\
	ffst::NODE()

#define FST_COMMENT LEX_COMMENT, IT::NO, 4,	\
	ffst::NODE(2, ffst::RELATION('#', 1), ffst::RELATION('#', 2)),\
	ffst::NODE(158,	\
	ffst::RELATION('a', 1), ffst::RELATION('b', 1), ffst::RELATION('c', 1), ffst::RELATION('d', 1), ffst::RELATION('e', 1), ffst::RELATION('f', 1),\
	ffst::RELATION('g', 1), ffst::RELATION('h', 1), ffst::RELATION('i', 1), ffst::RELATION('j', 1), ffst::RELATION('k', 1), ffst::RELATION('l', 1),\
	ffst::RELATION('m', 1), ffst::RELATION('n', 1), ffst::RELATION('o', 1), ffst::RELATION('p', 1), ffst::RELATION('q', 1), ffst::RELATION('r', 1),\
	ffst::RELATION('s', 1), ffst::RELATION('t', 1), ffst::RELATION('u', 1), ffst::RELATION('v', 1), ffst::RELATION('w', 1), ffst::RELATION('x', 1),\
	ffst::RELATION('y', 1), ffst::RELATION('z', 1), ffst::RELATION('1', 1), ffst::RELATION('2', 1), ffst::RELATION('3', 1), ffst::RELATION('4', 1),\
	ffst::RELATION('5', 1), ffst::RELATION('6', 1), ffst::RELATION('7', 1), ffst::RELATION('8', 1), ffst::RELATION('9', 1), ffst::RELATION('0', 1),\
	\
	ffst::RELATION('à', 1), ffst::RELATION('á', 1), ffst::RELATION('â', 1), ffst::RELATION('ã', 1), ffst::RELATION('ä', 1), ffst::RELATION('å', 1),\
	ffst::RELATION('¸', 1), ffst::RELATION('æ', 1), ffst::RELATION('ç', 1), ffst::RELATION('è', 1), ffst::RELATION('é', 1), ffst::RELATION('ê', 1),\
	ffst::RELATION('ë', 1), ffst::RELATION('ì', 1), ffst::RELATION('í', 1), ffst::RELATION('î', 1), ffst::RELATION('ï', 1), ffst::RELATION('ð', 1),\
	ffst::RELATION('ñ', 1), ffst::RELATION('ò', 1), ffst::RELATION('ó', 1), ffst::RELATION('ô', 1), ffst::RELATION('õ', 1), ffst::RELATION('ö', 1),\
	ffst::RELATION('÷', 1), ffst::RELATION('ø', 1), ffst::RELATION('ù', 1), ffst::RELATION('ú', 1), ffst::RELATION('û', 1), ffst::RELATION('ü', 1),\
	ffst::RELATION('ý', 1), ffst::RELATION('þ', 1), ffst::RELATION('ÿ', 1), ffst::RELATION(' ', 1), ffst::RELATION('.', 1), ffst::RELATION(',', 1),\
	ffst::RELATION('?', 1), ffst::RELATION('!', 1), ffst::RELATION(';', 1), ffst::RELATION(':', 1), ffst::RELATION('-', 1), ffst::RELATION(')', 1),\
	ffst::RELATION('(', 1), \
	\
	ffst::RELATION('a', 2), ffst::RELATION('b', 2), ffst::RELATION('c', 2), ffst::RELATION('d', 2), ffst::RELATION('e', 2), ffst::RELATION('f', 2),\
	ffst::RELATION('g', 2), ffst::RELATION('h', 2), ffst::RELATION('i', 2), ffst::RELATION('j', 2), ffst::RELATION('k', 2), ffst::RELATION('l', 2),\
	ffst::RELATION('m', 2), ffst::RELATION('n', 2), ffst::RELATION('o', 2), ffst::RELATION('p', 2), ffst::RELATION('q', 2), ffst::RELATION('r', 2),\
	ffst::RELATION('s', 2), ffst::RELATION('t', 2), ffst::RELATION('u', 2), ffst::RELATION('v', 2), ffst::RELATION('w', 2), ffst::RELATION('x', 2),\
	ffst::RELATION('y', 2), ffst::RELATION('z', 2), ffst::RELATION('1', 2), ffst::RELATION('2', 2), ffst::RELATION('3', 2), ffst::RELATION('4', 2),\
	ffst::RELATION('5', 2), ffst::RELATION('6', 2), ffst::RELATION('7', 2), ffst::RELATION('8', 2), ffst::RELATION('9', 2), ffst::RELATION('0', 2),\
	\
	ffst::RELATION('à', 2), ffst::RELATION('á', 2), ffst::RELATION('â', 2), ffst::RELATION('ã', 2), ffst::RELATION('ä', 2), ffst::RELATION('å', 2),\
	ffst::RELATION('¸', 2), ffst::RELATION('æ', 2), ffst::RELATION('ç', 2), ffst::RELATION('è', 2), ffst::RELATION('é', 2), ffst::RELATION('ê', 2),\
	ffst::RELATION('ë', 2), ffst::RELATION('ì', 2), ffst::RELATION('í', 2), ffst::RELATION('î', 2), ffst::RELATION('ï', 2), ffst::RELATION('ð', 2),\
	ffst::RELATION('ñ', 2), ffst::RELATION('ò', 2), ffst::RELATION('ó', 2), ffst::RELATION('ô', 2), ffst::RELATION('õ', 2), ffst::RELATION('ö', 2),\
	ffst::RELATION('÷', 2), ffst::RELATION('ø', 2), ffst::RELATION('ù', 2), ffst::RELATION('ú', 2), ffst::RELATION('û', 2), ffst::RELATION('ü', 2),\
	ffst::RELATION('ý', 2), ffst::RELATION('þ', 2), ffst::RELATION('ÿ', 2), ffst::RELATION(' ', 2), ffst::RELATION('.', 2), ffst::RELATION(',', 2),\
	ffst::RELATION('?', 2), ffst::RELATION('!', 2), ffst::RELATION(';', 2), ffst::RELATION(':', 2), ffst::RELATION('-', 2), ffst::RELATION(')', 2),\
	ffst::RELATION('(', 2)),\
	\
	ffst::NODE(1, ffst::RELATION(';', 3)),\
	ffst::NODE()


#define FST_OP LEX_OPERATOR, IT::NO, 2,	\
	ffst::NODE(5, ffst::RELATION('+', 1), ffst::RELATION('-', 1), ffst::RELATION('*', 1), ffst::RELATION('/', 1), ffst::RELATION('%', 1)),\
	ffst::NODE()

#define FST_PLUS LEX_PLUS, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION('+', 1)),\
	ffst::NODE()

#define FST_MINUS LEX_MINUS, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION('-', 1)),\
	ffst::NODE()

#define FST_STAR LEX_STAR, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION('*', 1)),\
	ffst::NODE()

#define FST_DIRSLASH LEX_DIRSLASH, IT::NO, 2, \
	ffst::NODE(1, ffst::RELATION('/', 1)),\
	ffst::NODE()

#define FST_PROC LEX_PROC, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION('%', 1)),\
	ffst::NODE()

#define FST_COMMA LEX_COMMA, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION(',', 1)),\
	ffst::NODE()

#define FST_LEFTBRACE LEX_LEFTBRACE, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION('[', 1)),\
	ffst::NODE()

#define FST_BRACELET LEX_BRACELET, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION(']', 1)),\
	ffst::NODE()

#define FST_LEFTTHESIS LEX_LEFTTHESIS, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION('(', 1)),\
	ffst::NODE()

#define FST_RIGHTTHESIS LEX_RIGHTTHESIS, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION(')', 1)),\
	ffst::NODE()

#define FST_EQUAL LEX_EQUAL, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION('=', 1)),\
	ffst::NODE()

#define FST_SEPARATOR LEX_SEPARATOR, IT::NO, 2,	\
	ffst::NODE(1, ffst::RELATION(';', 1)),\
	ffst::NODE()