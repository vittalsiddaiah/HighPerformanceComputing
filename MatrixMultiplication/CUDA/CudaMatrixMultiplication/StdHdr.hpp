/// -----------------------------------------------------------------------
///// Title              : StdHdr.hpp
///// Project            : EE 5321 – CAE Simulation on HPC Systems
///// File               : StdHdr.hpp
///// -----------------------------------------------------------------------
///// Primary Contact    : v_s191@txstate.edu; vittal.siddaiah@gmail.com;
///// RegNo              : A04848680
///// Secondary Contact  :
///// Creation Date      : 10/Feb/2019 :: 22:44
///// -----------------------------------------------------------------------
///// Description :
/////
/////
///// -----------------------------------------------------------------------
///// Review :
/////
/////
/////
///// -----------------------------------------------------------------------
///// Copyright (c) 2019 Texas State University
///// -----------------------------------------------------------------------
#pragma once
///// -----------------------------------------------------------------------
///// Dependent Headers Definitions
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <cstdint>
#include <iomanip>
#include <limits.h>

using namespace std;
typedef std::ostream OStr_t;
#define DEC_T std::ios::dec
#define HEX_T std::ios::hex
#define GetCurrentTimeUS(__tme) {  struct timeval __tv;  gettimeofday(&__tv,NULL); __tme = ((1e+6 * __tv.tv_sec) + __tv.tv_usec);  }
#define NanoSecs2Secs(__timeInNanoSecs) ((__timeInNanoSecs)*1e-6)
#define Rand ((((float)rand()/(float)(RAND_MAX)) * 400)-200)
inline OStr_t &Dec02_f(OStr_t &_S)  { _S.width(02), _S.fill('0'), _S.unsetf(HEX_T), _S.setf(DEC_T); return _S;  }
inline OStr_t &Dec04_f(OStr_t &_S)  { _S.width(04), _S.fill('0'), _S.unsetf(HEX_T), _S.setf(DEC_T); return _S;  }
inline OStr_t &FAvg_f(OStr_t &_S)   { setprecision(4), _S.width(10), _S.fill(' '); return _S; }

std::string TimeStamp()    {
        std::stringstream ts;
        time_t tt;
        struct tm * ti;
        time (&tt);
        ti = localtime(&tt);
        ts << Dec04_f << 1900 + ti->tm_year;
        ts << Dec02_f << 1 + ti->tm_mon ;
        ts << Dec02_f << ti->tm_mday;
        ts << Dec02_f << ti->tm_hour;
        ts << Dec02_f << ti->tm_min;
        ts << Dec02_f << ti->tm_sec;
        return ts.str();
}




std::string Label()	{
	std::stringstream label;
	label << "******************************************* HomeWork : 5 *******************************************" << std::endl;
	label << "*                                     Version 0.4 (CUDA Programming)                               *" << std::endl;
	label << "*                              EE 5321 CAE Simulation on HPC Systems                               *" << std::endl;
	label << "*                        Contact: (Vittal) v_s191@txstate.edu  (A04848680)                         *" << std::endl;
	label << "*                                      Texas State University                                      *" << std::endl;
	label << "****************************************************************************************************" << std::endl;
	return label.str();
}


