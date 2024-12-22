#include "stdafx.h"
#include "Polish.h"

#define FILE "D:\\Visual_Lab_3sem\\Course_Project_MAI_2024\\MAI2024\\ASM\\ASM.asm"

int _tmain(int argc, wchar_t* argv[])
{
	argc = 2;
	argv = new wchar_t* [2];
	wchar_t* filename = (wchar_t*)L"-in:D:\\Visual_Lab_3sem\\Course_Project_MAI_2024\\MAI.txt";
	argv[1] = filename;

	setlocale(LC_ALL, "ru");
	Log::LOG	log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);

		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
	Log:WriteIn(log, in);

		std::vector<ffst::FST> fsts{
			ffst::FST(FST_NEW),
			ffst::FST(FST_UNTIL),
			ffst::FST(FST_INTEGER),
			ffst::FST(FST_STRING),
			ffst::FST(FST_FUNCTION),
			ffst::FST(FST_RETURN),
			ffst::FST(FST_PRINT),
			ffst::FST(FST_HEAD),
			ffst::FST(FST_OCT),
			ffst::FST(FST_BIN),
			ffst::FST(FST_INTLIT),
			ffst::FST(FST_STRLIT),
			ffst::FST(FST_COMMENT),
			ffst::FST(FST_ID),
			ffst::FST(FST_OP),
			ffst::FST(FST_COMMA),
			ffst::FST(FST_LEFTBRACE),
			ffst::FST(FST_BRACELET),
			ffst::FST(FST_LEFTTHESIS),
			ffst::FST(FST_RIGHTTHESIS),
			ffst::FST(FST_EQUAL),
			ffst::FST(FST_SEPARATOR)
		};

		Lex::LEX lex = Lex::LexicalAnalysis(log, in, fsts);
		Lex::LTLog(lex.lextable, log);
		Lex::ITLog(lex.idtable, log);
		std::cout << "Лексический анализ выполнен успешно." << std::endl;


		MFST_TRACE_START
			MFST::Mfst mfst(lex.lextable, GRB::getGreibach());
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);
		std::cout << "Синтаксический анализ выполнен успешно." << std::endl;

		Sem::CheckAssignValue(log, lex.lextable, lex.idtable);
		Sem::CheckAllowedValue(log, lex.lextable, lex.idtable);
		Sem::CheckReturnType(log, lex.lextable, lex.idtable);
		Sem::CheckParm(log, lex.lextable, lex.idtable);
		Sem::CheckNativeParm(log, lex.lextable, lex.idtable);
		Sem::CheckFunc(log, lex.lextable, lex.idtable);
		std::cout << "Семантический анализ выполнен успешно." << std::endl;

		CG::ConstSegment CnstS(lex.idtable.size);
		CG::DataSegment Data(lex.idtable.size);
		CG::CodeSegment Code;
		CG::add(lex.idtable, CnstS);
		CG::add(lex.idtable, Data);
		CG::CodeSegmentGeneration(Code, lex.lextable, lex.idtable);
		CG::startGeneration(FILE, CnstS, Data, Code);
		std::cout << "Генерация кода выполнена успешно." << std::endl;
		
		WritePolishNotationToFile("D:\\Visual_Lab_3sem\\Course_Project_MAI_2024\\MAI2024\\poliz\\poliz.txt", lex.lextable, lex.idtable);
		Log::Close(log);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;

}