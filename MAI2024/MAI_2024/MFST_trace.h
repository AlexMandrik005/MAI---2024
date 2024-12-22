#pragma once
#include "Greibach.h"
#include "Log.h"
#include <iomanip>

#define MFST_TRACE_START {*log.stream<< std::setw(4)<<std::left<<"Шаг"<<":"\
								  << std::setw(20)<<std::left<<"Правило"\
								  << std::setw(30)<<std::left<<"Входная лента"\
								  << std::setw(20)<<std::left<<"Стек"\
								  << std::endl;}

#define MFST_TRACE1		{*log.stream<< std::setw(4)<<std::left<<++FST_TRACE_n<<": "\
								  << std::setw(20)<<std::left<<rule.getCRule(rbuf,nrulechain)\
								  << std::setw(30)<<std::left<<getCLenta(lbuf,lenta_position)\
								  << std::setw(20)<<std::left<<getCSt(sbuf)\
								  << std::endl;}

#define MFST_TRACE2		{*log.stream<< std::setw(4)<<std::left<<FST_TRACE_n<<": "\
								  << std::setw(20)<<std::left<<" "\
								  << std::setw(30)<<std::left<<getCLenta(lbuf,lenta_position)\
								  << std::setw(20)<<std::left<<getCSt(sbuf)\
								  << std::endl;}

#define MFST_TRACE3		{*log.stream<< std::setw(4)<<std::left<<++FST_TRACE_n<<": "\
								  << std::setw(20)<<std::left<<" "\
								  << std::setw(30)<<std::left<<getCLenta(lbuf,lenta_position)\
								  << std::setw(20)<<std::left<<getCSt(sbuf)\
								  << std::endl;}

#define MFST_TRACE4(c)		*log.stream<<std::setw(4)<<std::left << ++FST_TRACE_n << ": "<<std::setw(20)<< std::left <<c<<std::endl;
#define MFST_TRACE5(c)		*log.stream<<std::setw(4)<<std::left << FST_TRACE_n << ": "<<std::setw(20)<< std::left <<c<<std::endl;
#define MFST_TRACE6(c,k)	*log.stream<<std::setw(4)<<std::left << FST_TRACE_n << ": "<<std::setw(20)<< std::left <<c << k <<std::endl;
#define MFST_TRACE7			*log.stream<<std::setw(4)<<std::left << state.lenta_position << ": "\
							<<std::setw(20)<< std::left << rule.getCRule(rbuf,state.nrulechain)\
							<<std::endl;

