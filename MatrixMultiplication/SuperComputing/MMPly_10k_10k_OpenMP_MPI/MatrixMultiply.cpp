#include "StdHdr.hpp"
#include <mpi.h>
#include <omp.h>

auto main(int argc, char **argv)-> int    {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Process input arguments
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int matrixSize = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	auto fileTiming = TimeStamp();
	//std::string targetDirectory = "/home/v_s191/MatrixPerformance/log/";
	std::string targetDirectory ="";
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MPI Start
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int32_t worldRank;
	int32_t worldSize;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	uint64_t beginTotTime, endTotTime;
	if(!worldRank)	{
		std::cout << Label() << std::endl;
		GetCurrentTimeUS(beginTotTime);
	}
	std::cout << " Begining Rank " <<  worldRank << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Memory Allocation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float **_lhs, **_rhs, **_avg;
	_lhs = new float*[matrixSize];
	_rhs = new float*[matrixSize];
	_avg = new float*[matrixSize];
	#pragma omp parallel 
	for(size_t i=0; i< matrixSize; i++) {
		_lhs[i] = new float[matrixSize];
		_rhs[i] = new float[matrixSize];
		_avg[i] = new float[matrixSize];
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float _avgMplyTme = 0.0;
	float _avgRndTme = 0.0;
	//bool isTesting = true;
	bool isTesting = false;
	float _minMplyTme = (float)9999.99;
	std::cout << "Iterations, RndTimeSecs, AvgRndTimeSecs, MplyTimeSecs, AvgMplyTimeSecs, MinMplyTime" << std::endl;
	for(size_t iter = 0; iter < iterations; iter++)   {   //Iterations Start Here
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Randomize Input
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		uint64_t beginRndTime, endRndTime;
		GetCurrentTimeUS(beginRndTime);

		if(!isTesting)    {
		//#pragma omp parallel for shared(_lhs, _rhs) private(row, col)
			for(size_t row=0; row < matrixSize; row++) {
				for(size_t col=0; col < matrixSize; col++)
					_lhs[row][col]  = Rand, _rhs[row][col]  = Rand;
			}
		}
		else    {   //Fill Random values Start
			for(size_t row=0; row < matrixSize; row++) {
				for(size_t col=0; col < matrixSize; col++)
					_lhs[row][col]  = 2, _rhs[row][col]  = 2;
			}
		}   //Fill Random values End
		GetCurrentTimeUS(endRndTime);
		double rndTimeSecs = NanoSecs2Secs(endRndTime - beginRndTime);
		_avgRndTme += rndTimeSecs;
		setprecision(6);
		std::cout << "      " << Dec04_f <<  (iter+1) << ",  " << FAvg_f <<  rndTimeSecs << ",     "  << FAvg_f << (_avgRndTme/(iter+1)) << ",   ";
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Matrix Multiplication Start Here
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		uint64_t beginMpyTime, endMpyTime;
		size_t i, j, k;
		GetCurrentTimeUS(beginMpyTime);
		#pragma omp parallel for private(j, k)
		for (i = 0; i < matrixSize; i++)    {           //Matrix Multiplication Starts Here
			for (j = 0; j < matrixSize; j++)	
				for(k =0; k <matrixSize; k++)	
					_avg[i][j] += _lhs[i][k] * _rhs[k][j];		
		}       //Matrix Multiplication Ends Here
		GetCurrentTimeUS(endMpyTime);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Matrix Multiplication End Here
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		double mpyTimeSecs = NanoSecs2Secs(endMpyTime - beginMpyTime);
		_avgMplyTme += mpyTimeSecs;
		_minMplyTme = (mpyTimeSecs < _minMplyTme)? mpyTimeSecs: _minMplyTme;
		std::cout  << FAvg_f <<  mpyTimeSecs << ",      " << FAvg_f <<  (_avgMplyTme/(iter+1))  << ",  " << FAvg_f<< _minMplyTme << std::endl;

	}   //Iterations Close Here

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Average Matrix and Log to the file in CSV format
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	std::stringstream avgfile;
//	avgfile << targetDirectory << "ICPC_Average_"  << Dec02_f << worldRank << "_" << fileTiming << ".csv";
//	std::ofstream avgCSV_f;
//	avgCSV_f.open(avgfile.str().c_str());
	for (int row = 0; row < matrixSize; row++)  {        //Averaging the Matrix Start
		for (int col = 0; col < matrixSize; col++)
			 _avg[row][col] /= (float)iterations;
		//avgCSV_f << std::endl;
	}   //Averaging the Matrix Done
	//avgCSV_f.close();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Report the final output in CSV Format
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char hostName[1024];
	char userName[1024];
	gethostname(hostName, 1024);
	getlogin_r(userName, 1024);

	std::stringstream sstr;
	sstr << targetDirectory << "ICPC_Report_" << Dec02_f << worldRank << "_" << fileTiming << ".csv";
	std::ofstream rptCSV_f;
	rptCSV_f.open(sstr.str().c_str());
	rptCSV_f << "MatrixSize, Iterations, HostName, UserName, AvgRndTimeSecs, AvgMultiplyTimeSecs, BestMultiplyTimeSecs, TotalTimeSecs" << std::endl;
	rptCSV_f << matrixSize << ", " << iterations << ", "  \
			<< userName << ", " <<  hostName << ", " \
			<< FAvg_f << _avgRndTme/iterations  << ", " \
			<< FAvg_f << _avgMplyTme/iterations << ", " \
			<< FAvg_f << _minMplyTme << ", "  << std::endl;
			//<< FAvg_f << totTimeSecs << std::endl;

	rptCSV_f.close();
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "                    Matrix Size : " << matrixSize << " x " << matrixSize << std::endl;
	std::cout << "                     Iterations : " << iterations << std::endl;
	std::cout << "                      Host Name : " << hostName << std::endl;
	std::cout << "                      User Name : " << userName << std::endl;
	std::cout << "Average Random Number Fill Time : " << FAvg_f << _avgRndTme/iterations  << " secs." << std::endl;
	std::cout << "   Average Matrix Multiply Time : " << FAvg_f << _avgMplyTme/iterations << " secs." << std::endl;
	std::cout << "             Best Multiply Time : " << FAvg_f << _minMplyTme << " secs." << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;


	std::cout << "The Following files were generated: " << std::endl;
	std::cout << " Report  File : " << sstr.str().c_str() << std::endl;
	std::cout << " Terminating Rank " <<  worldRank << std::endl;

	MPI_Reduce(_avg, _rhs, 1, MPI_FLOAT, MPI_SUM, 0,MPI_COMM_WORLD);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Memory De-Allocation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (NULL != _lhs) delete[]_lhs;
	if (NULL != _avg) delete[]_avg;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	MPI_Barrier(MPI_COMM_WORLD);
	
	if(!worldRank)	{
		std::stringstream avgfile;
      		avgfile << targetDirectory << "ICPC_Average_"  << Dec02_f << worldRank << "_" << fileTiming << ".csv";
      		std::ofstream avgCSV_f;
      		avgCSV_f.open(avgfile.str().c_str());
       		for (int row = 0; row < matrixSize; row++)  {        //Averaging the Matrix Start
                	for (int col = 0; col < matrixSize; col++)
                        	_rhs[row][col] /= (float)worldSize;
                	avgCSV_f << std::endl;
		std::cout << " Average File : " << avgfile.str().c_str() << std::endl;
        }   //Averaging the Matrix Done
        avgCSV_f.close();
	
		GetCurrentTimeUS(endTotTime);
		double totTimeSecs = NanoSecs2Secs(endTotTime - beginTotTime);
		std::cout << "                     Total time : " << FAvg_f << totTimeSecs << " secs." << std::endl;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Memory De-Allocation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (NULL != _rhs) delete[]_rhs;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MPI_Finalize();
	return 0;
}
