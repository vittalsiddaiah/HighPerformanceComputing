#include "StdLib.hpp"
#include "Matrix.hpp"

auto Assignment_01() {
	//------------------------------------------------------------------------------------------------------------------
	//Part-1 Focused Testing
	//------------------------------------------------------------------------------------------------------------------
	{
		std::cout << "Part -1: Focused Testing Started\n" << StdLib::SingleLine << std::endl;
		VectorDouble2D_t lhs{
				{2.3300,   4.5300,   -98.4000},
				{28.5400,  -75.6000, 23.4400},
				{102.3300, 3.3000,   -45.0100}
		};

		VectorDouble2D_t rhs{
				{46.73,  43.6,   92.1},
				{-2.233, -116.8, -11.4},
				{156.8,  13.44,  67.8}
		};
		Matrix::Matrix().FocusedTesting(lhs, rhs);
		std::cout << "Part -1: Focused Testing Completed\n" << StdLib::DoubleLine << std::endl;
	}
	//==================================================================================================================

	//------------------------------------------------------------------------------------------------------------------
	//Part-2 Random Testing
	//------------------------------------------------------------------------------------------------------------------
	{
		std::cout << "Part -2: Random Testing Started (Random Testing for 3 x 3 Matrix) \n" << StdLib::SingleLine
		          << std::endl;
		size_t matrixSize = 3;
		VectorDouble2D_t result;
		Matrix::Matrix().RandomTesting(matrixSize, result, true);
		std::cout << "Part -2: Random Testing Completed\n" << StdLib::DoubleLine << std::endl;
	}
	//==================================================================================================================

	//------------------------------------------------------------------------------------------------------------------
	//Part-3 Average of n iterations; n=100;
	//------------------------------------------------------------------------------------------------------------------
	{
		std::cout << "Part -3: Average of n iterations Started \n" << StdLib::SingleLine << std::endl;
		size_t matrixSize = 3;
		size_t iterations = 100;
		VectorDouble3D_t resultMatrixx;
		VectorDouble2D_t averageMatrix(matrixSize, std::vector<double>(matrixSize));

		Matrix::Matrix().Regression(iterations, matrixSize, resultMatrixx);
		std::cout << "\n Computing Average ..." << std::endl;
		for (const auto &matrix: resultMatrixx) {
			size_t vecId = 0;
			//Matrix::Matrix().PrintMatrix(matrix);
			for (const auto &vec: matrix) {
				std::transform(vec.begin(), vec.end(), averageMatrix[vecId].begin(), averageMatrix[vecId].begin()
						, std::plus<>());
				vecId++;
			}
		}

		for (auto &vec1d: averageMatrix) {
			for (auto &element: vec1d) element /= double_t(iterations);
		}
		std::cout << "Average of " << iterations << " iteration(s) of " << matrixSize << " x " << matrixSize \
 << " random matrix  : \n Average = " << std::endl;

		Matrix::Matrix().PrintMatrix(averageMatrix);
		std::cout << "Part -3: Average of n iterations Completed\n" << StdLib::DoubleLine << std::endl;
	}
	//==================================================================================================================
}

auto main(int argc, char **argv) -> int{
	std::cout << StdLib::Label() << std::endl;
	Assignment_01();
	std::cout << "Assignment 01 Completed Successfully....\n" << StdLib::DoubleLine << std::endl;
	return 0;
}
