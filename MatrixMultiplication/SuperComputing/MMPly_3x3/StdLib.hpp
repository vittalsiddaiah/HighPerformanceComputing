/// -----------------------------------------------------------------------
/// Title              : StdLib.hpp
/// Project            : EE 5321 – CAE Simulation on HPC Systems
/// File               : StdLib.hpp
/// -----------------------------------------------------------------------
/// Primary Contact    : v_s191@txstate.edu; vittal.siddaiah@gmail.com;
/// RegNo              : A04848680
/// Secondary Contact  :
/// Creation Date      : 29/Jan/2019 :: 23:06
/// -----------------------------------------------------------------------
/// Description :
///
///
/// -----------------------------------------------------------------------
/// Review :
///
///
///
/// -----------------------------------------------------------------------
/// Copyright (c) 2019 Texas State University
/// -----------------------------------------------------------------------
#pragma once
/// -----------------------------------------------------------------------
/// Dependent Headers Definitions
#include "StdHdr.hpp"
/// -----------------------------------------------------------------------

namespace StdLib {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! @class StdLib
    @author vittal siddaiah , @date 29/Jan/2019
    @brief Description:
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Timer {
		typedef std::chrono::high_resolution_clock chrono_hr_clk;
	private:
		Str_t ConvertTimeString(double timeInSecs) {
			uint32_t hrs = 0;
			uint32_t mins = 0;
			double secs = 0.0;
			StrStream_t str;
			hrs = uint32_t(timeInSecs / (60.0 * 60.0));
			mins = uint32_t((timeInSecs - double(uint32_t(hrs * 60.0 * 60.0))) / 60.0);
			secs = (timeInSecs - ((hrs * 60) + (mins * 60)));
			str << "[" << std::setfill('0') << std::setw(2) << hrs << ":" << std::setw(2) << mins << ":";
			str << std::setw(5) << std::setfill('0') << std::setprecision(3) << secs << "]";
			return str.str();
		}

	public:
		Timer() : _start(chrono_hr_clk::now()) {}

		void Reset() { _start = chrono_hr_clk::now(); }

		double Elapsed() const {
			return std::chrono::duration_cast<std::chrono::duration<double>>(chrono_hr_clk::now() - _start).count();
		}

		Str_t ElapseSTR() {
			return this->ConvertTimeString(this->Elapsed());
		}

	private:
		chrono_hr_clk::time_point _start;
	};

	auto inline Label() {
		std::stringstream label;
		label << "******************************************* HomeWork : 1 *******************************************"
		      << std::endl;
		label << "*                                           Version 0.2                                            *"
		      << std::endl;
		label << "*                              EE 5321 CAE Simulation on HPC Systems                               *"
		      << std::endl;
		label << "*                        Contact: (Vittal) v_s191@txstate.edu  (A04848680)                         *"
		      << std::endl;
		label << "*                                      Texas State University                                      *"
		      << std::endl;
		label << "****************************************************************************************************"
		      << std::endl;
		return label.str();
	}

	auto inline SingleLine = std::string(
			"----------------------------------------------------------------------------------------------------");
	auto inline DoubleLine = std::string(
			"====================================================================================================");

}   // Namespace Closed...
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////