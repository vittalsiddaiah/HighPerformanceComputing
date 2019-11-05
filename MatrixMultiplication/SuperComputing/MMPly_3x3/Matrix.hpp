/// -----------------------------------------------------------------------
/// Title              : Matrix.hpp
/// Project            : EE 5321 – CAE Simulation on HPC Systems
/// File               : Matrix.hpp
/// -----------------------------------------------------------------------
/// Primary Contact    : v_s191@txstate.edu; vittal.siddaiah@gmail.com;
/// RegNo              : A04848680
/// Secondary Contact  :
/// Creation Date      : 30/Jan/2019 :: 00:02
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
#include "StdLib.hpp"
/// -----------------------------------------------------------------------

namespace Matrix {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! @class Matrix
    @author vittal siddaiah , @date 30/Jan/2019
    @brief Description:
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Matrix {
    public:
        //Print Matrix Code
        void PrintMatrix(const VectorDouble2D_t &result)   {
            std::cout << "\t";
            for (const auto& vector1D : result)  {
                for (const auto& value : vector1D)   {
                    std::cout << value << ", ";
                }
                std::cout << std::endl << "\t";
            }
            std::cout << std::endl;
        }
        //Focused-testing the results against standard vectors
        auto FocusedTesting(const VectorDouble2D_t &lhs, const VectorDouble2D_t &rhs) {
            std::cout << "lhs = " << std::endl;
            PrintMatrix(lhs);
            std::cout << std::endl;
            std::cout << "rhs = " << std::endl;
            PrintMatrix(rhs);
            std::cout << std::endl;
            VectorDouble2D_t result = Multiply(lhs, rhs, 3);
            std::cout << "result = " << std::endl;
            PrintMatrix(result);
            return result;
        }

        //Code for unit-testing the results against standard vectors
        auto RandomTesting(std::size_t matrixSize, VectorDouble2D_t &result, bool printResult=false)    {
            VectorDouble2D_t lhs( matrixSize, std::vector<double>(matrixSize));
            VectorDouble2D_t rhs( matrixSize, std::vector<double>(matrixSize));
            RandomVector(lhs, matrixSize);
            RandomVector(rhs, matrixSize);
            if(printResult) {
                std::cout << "lhs = " << std::endl;
                PrintMatrix(lhs);
                std::cout << std::endl;
                std::cout << "rhs = " << std::endl;
                PrintMatrix(rhs);
                std::cout << std::endl;
            }
            StdLib::Timer timing;
            timing.Reset();
            result = Multiply(lhs, rhs, matrixSize);
            auto timeElapsed = timing.Elapsed();
            if(printResult) std::cout << "result = " << std::endl, PrintMatrix(result);
            return timeElapsed;
        }

        //Code for regression
        std::vector<double> Regression(std::size_t iterations, std::size_t matrixSize, VectorDouble3D_t &resultMatrixx) {
            std::vector<double> timingVector;
            std::size_t regressionCount = 0;
            std::cout << iterations << std::endl;
            for(regressionCount =0; regressionCount <iterations; regressionCount++)   {
                std::cout << ".";
                if(((regressionCount+1)%10)==0) std::cout << std::endl;
                VectorDouble2D_t result(matrixSize, std::vector<double>(matrixSize));
                auto timing = RandomTesting(matrixSize, result, false);
                resultMatrixx.push_back(result);
                timingVector.push_back(timing);
            }
            return timingVector;
        }

    private:
        //Generate Random Vector
        void RandomVector(VectorDouble2D_t &result, std::size_t vectorSize)    {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> uniformRealDistribution(-199.0, 199.0);
            //std::normal_distribution<> normalDistribution(0, 30.0);
            for( auto &unitVec: result)    {
                for( auto &unit: unitVec) {
                    unit = uniformRealDistribution(gen);
                }
            }
            //PrintMatrix(result);
        }



        //Multiplication Code
        VectorDouble2D_t Multiply(VectorDouble2D_t lhs, VectorDouble2D_t rhs , std::size_t matrixSize)   {
            VectorDouble2D_t result( matrixSize, std::vector<double>(matrixSize));
            for (size_t i = 0; i < matrixSize; i++) {
                for (size_t j = 0; j < matrixSize; j++) {
                    float value = 0;
                    for (size_t k = 0; k < matrixSize; k++) {
                        value += lhs[i][k] * rhs[k][j];
                    }
                    result[i][j] = value;
                }
            }
            return result;
        }


    };
}   // Namespace Closed...

