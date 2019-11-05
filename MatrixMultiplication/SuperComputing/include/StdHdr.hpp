/// --------------------------------------------------------------------------------------------------------------------
/// Title              : StdHdr.hpp
/// Project            : EE 5321 – CAE Simulation on HPC Systems
/// File               : StdHdr.hpp
/// --------------------------------------------------------------------------------------------------------------------
/// Primary Contact    : v_s191@txstate.edu; vittal.siddaiah@gmail.com;
/// RegNo              : A04848680
/// Secondary Contact  :
/// Creation Date      : 29/Jan/2019 :: 21:26
/// --------------------------------------------------------------------------------------------------------------------
/// Description :
///
///
/// --------------------------------------------------------------------------------------------------------------------
/// Review :
///
///
///
/// --------------------------------------------------------------------------------------------------------------------
/// Copyright (c) 2019 Texas State University
/// --------------------------------------------------------------------------------------------------------------------
#pragma once
/// --------------------------------------------------------------------------------------------------------------------
/// Dependent Headers Definitions
/// C++ STL Headers
#include <iostream>
#include <thread>
#include <iomanip>
#include <numeric>
#include <map>
#include <ctime>
#include <bitset>
#include <limits>
#include <string>
#include <vector>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cassert>
#include <exception>
#include <algorithm>
#include <functional>
#include <random>
#include <regex>
#include <tuple>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Boost Headers

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Project Types
typedef std::string Str_t;
typedef std::stringstream StrStream_t;
typedef std::vector< std::vector<double> >  VectorDouble2D_t;
typedef std::vector< std::vector< std::vector<double> > >  VectorDouble3D_t;

static const Str_t Project("EE 5321 – CAE Simulation on HPC Systems \n         Texas State University         ");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////