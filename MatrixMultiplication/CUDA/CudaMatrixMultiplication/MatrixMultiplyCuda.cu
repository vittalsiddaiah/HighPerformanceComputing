#include <stdio.h>
#include <fcntl.h>
#include <cuda.h>
#include <stdlib.h>
#include <iostream>
#include "StdHdr.hpp"


#define CUDA_TILE_SIZE 64
#define GridSize(matrixSize) (uint32_t)ceil((float)(matrixSize)/(float)CUDA_TILE_SIZE)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CUDA PROGRAMMING: Kernel Function
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__global__ void DeviceMatrixMultiply(float *ptrLhs, float *ptrRhs, float *ptrAvg, int matrixSize)  {
    //CUDA Tile Declarations
    __shared__ float lhs[CUDA_TILE_SIZE][CUDA_TILE_SIZE];
    __shared__ float rhs[CUDA_TILE_SIZE][CUDA_TILE_SIZE];

    //Initialized the allocated block to Zero
    //TODO Need to check if this step is required as we are copying the data from the source...
    lhs[threadIdx.y][threadIdx.x] = 0.0;
    rhs[threadIdx.y][threadIdx.x] = 0.0;

    // ids of thread
    int Row = blockDim.y*blockIdx.y + threadIdx.y;
    int Col = blockDim.x*blockIdx.x + threadIdx.x;
    float product = 0.0;


    for (int k = 0; k < (((matrixSize - 1)/ CUDA_TILE_SIZE) + 1); k++)  {
        if ((Row < matrixSize) && (threadIdx.x + (k*CUDA_TILE_SIZE)) < matrixSize)
            lhs[threadIdx.y][threadIdx.x] = ptrLhs[(Row*matrixSize) + threadIdx.x + (k*CUDA_TILE_SIZE)];
        else
            lhs[threadIdx.y][threadIdx.x] = 0.0; // if outside the boundaries of the matrix

        if ((Col < matrixSize) && (threadIdx.y + k*CUDA_TILE_SIZE) < matrixSize)
            rhs[threadIdx.y][threadIdx.x] = ptrRhs[(threadIdx.y + k*CUDA_TILE_SIZE)*matrixSize + Col];
        else
            rhs[threadIdx.y][threadIdx.x] = 0.0; //if outside the boundary of the matrix

        // making sure all threads have arrived before multiplications
        __syncthreads();

        // multiplying elements present in the current tile
        for (int j = 0; j < CUDA_TILE_SIZE; ++j)
            product += lhs[threadIdx.y][j] * rhs[j][threadIdx.x];  //Product of each thread

    }

    // Saving final result to Matrix C
    if (Row < matrixSize && Col < matrixSize) {
        ptrAvg[Row*matrixSize + Col] = product;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Host side code (Compiled for General Purpose
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv) {
    std::cout << Label() << std::endl;
    uint64_t beginTotTime, endTotTime;
    GetCurrentTimeUS(beginTotTime);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Process input arguments.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int matrixSize = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    uint64_t totalSize = matrixSize*matrixSize;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Host Side Memory Allocations.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    float *hostLhs;
    float *hostRhs;
    float *hostAvg;
    hostLhs = new float[totalSize];
    hostRhs = new float[totalSize];
    hostAvg = new float[totalSize];
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Device/GPU Side Memory Allocations.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    float *deviceLhs;
    float *deviceRhs;
    float *deviceAvg;
    cudaMalloc((void **)&deviceLhs, sizeof(float)*totalSize);
    cudaMalloc((void **)&deviceRhs, sizeof(float)*totalSize);
    cudaMalloc((void **)&deviceAvg, sizeof(float)*totalSize);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    std::cout << "  HostRand,AvgHostRand,   MemcpH2C,AvgMemcpH2C,  MMPlyCuda,AvgMMPlyCuda,MinMMPlyCuda,  MemcpC2H,AvgMemcpC2H" << std::endl << std::flush;
    double avgRandTime = 0.0, avgMemCpH2C = 0.0, avgMmply = 0.0, avgMemCpC2H = 0.0, minMmply = 999.0;
    for(size_t iteration = 1; iteration < iterations+1; iteration++)  {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Host size vector randomization
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //OMP Parallel if required here...
        uint64_t beginRndTime, endRndTime;
        GetCurrentTimeUS(beginRndTime);
        for(size_t offset=0; offset < totalSize; offset++)
            hostLhs[offset]  = Rand, hostRhs[offset]  = Rand;
        GetCurrentTimeUS(endRndTime);
        double randTimeSecs = NanoSecs2Secs(endRndTime - beginRndTime);
        //std::cout << "Randomization Completed in     : " << randTimeSecs << "Secs. " << std::endl << std::flush;
        avgRandTime += randTimeSecs;
        std::cout << FAvg_f << randTimeSecs << ", " << FAvg_f << (avgRandTime/iteration) << ", " << std::flush;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Memory Copy From CPU addressable memory to GPU addressable memory
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        uint64_t beginCmcpyTime, endCmcpyTime;
        GetCurrentTimeUS(beginCmcpyTime);
        cudaMemcpy(deviceLhs, hostLhs, sizeof(float)*totalSize, cudaMemcpyHostToDevice);
        cudaMemcpy(deviceRhs, hostRhs, sizeof(float)*totalSize, cudaMemcpyHostToDevice);
        GetCurrentTimeUS(endCmcpyTime);
        double cudaMemCpyTimeSecs = NanoSecs2Secs(endCmcpyTime - beginCmcpyTime);
        avgMemCpH2C += cudaMemCpyTimeSecs;
        //std::cout << "Host 2 Cuda Memcpy Completed in     : " << cudaMemCpyTimeSecs << "Secs. " << std::endl << std::flush;
        std::cout << FAvg_f << cudaMemCpyTimeSecs << ", " << FAvg_f << (avgMemCpH2C/iteration) << ", " << std::flush;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Defining CUDA topology/configuration, Initializing the Grid and Block dimensions
        // (dim3 is an integer vector type that can be used in CUDA code.)
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //uint32_t gridSize = (uint32_t)ceil((float)matrixSize/(float)CUDA_TILE_SIZE);
        dim3 dimGrid(GridSize(matrixSize), GridSize(matrixSize), 1);
        dim3 dimBlock(CUDA_TILE_SIZE, CUDA_TILE_SIZE, 1);

        uint64_t beginMpyTime, endMpyTime;
        GetCurrentTimeUS(beginMpyTime);
        DeviceMatrixMultiply<<<dimGrid, dimBlock>>>(deviceLhs, deviceRhs, deviceAvg, matrixSize);
        GetCurrentTimeUS(endMpyTime);
        double mplyEndTimeSecs = NanoSecs2Secs(endMpyTime - beginMpyTime);
        avgMmply += mplyEndTimeSecs;
        minMmply = (mplyEndTimeSecs < minMmply) ? mplyEndTimeSecs : minMmply;
        //std::cout << "CUDA Multiplication Completed in :" << mplyEndTimeSecs << "Secs. "<< std::endl << std::flush;
        std::cout << FAvg_f << mplyEndTimeSecs << ", " << FAvg_f << (avgMmply/iteration) << ", " << FAvg_f << minMmply << ", "<< std::flush;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Another way to sync theads from the GPU
        cudaDeviceSynchronize();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Memory Copy From GPU memory to CPU addressable memory
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        uint64_t beginCMcpyTime, endCMcpyTime;
        GetCurrentTimeUS(beginCMcpyTime);
        cudaMemcpy(hostRhs, deviceAvg, sizeof(float)*totalSize, cudaMemcpyDeviceToHost);
        for(size_t offset=0; offset < totalSize; offset++) hostAvg[offset] += hostRhs[offset];
        GetCurrentTimeUS(endCMcpyTime);
        double cudaMEMCpyTimeSecs = NanoSecs2Secs(endCMcpyTime - beginCMcpyTime);
        avgMemCpC2H += cudaMEMCpyTimeSecs;
        //std::cout << "Cuda 2 Host Memcpy Completed in     : " << cudaMEMCpyTimeSecs << "Secs. " << std::endl << std::flush;
        std::cout << FAvg_f << cudaMEMCpyTimeSecs << ", " << FAvg_f << (avgMemCpC2H/iteration) << ", " << std::endl << std::flush;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    for(size_t offset=0; offset < totalSize; offset++) hostAvg[offset] /=iterations;
    int fd_avgFile = open("CudaAverageMatrixFile.dat",O_CREAT|O_WRONLY,0775);
    int bytesWritten;
    if(fd_avgFile >0)   {
        if ((bytesWritten = write(fd_avgFile, hostAvg, sizeof(*hostAvg)*totalSize)) == -1)
            std::cerr << "Error in writing to the file ..." << bytesWritten << " Bytes written" << std::endl << std::flush;
        close(fd_avgFile);
     }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Memory De-Allocation of Cuda target / Device Memory
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (NULL != deviceLhs) cudaFree(deviceLhs);
    if (NULL != deviceRhs) cudaFree(deviceRhs);
    if (NULL != deviceAvg) cudaFree(deviceAvg);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Memory De-Allocation of host Memory
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (NULL != hostLhs) delete[]hostLhs;
    if (NULL != hostRhs) delete[]hostRhs;
    if (NULL != hostAvg) delete[]hostAvg;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "Program Execution Completed " << std::endl << std::flush;
    GetCurrentTimeUS(endTotTime);
    double totTimeSecs = NanoSecs2Secs(endTotTime - beginTotTime);

    char hostName[64];
    char userName[64];
    gethostname(hostName, 64);
    getlogin_r(userName, 64);

    std::stringstream sstr;
    sstr << "Cuda_Score_Card_" << TimeStamp() << ".txt";
    std::ofstream rptTxt_f;
    rptTxt_f.open(sstr.str().c_str());
    rptTxt_f << "-----------------   Cuda Matrix Multiplication Score Card -----------------" << std::endl;
    rptTxt_f << "                        Matrix Size : " << matrixSize << " x " << matrixSize << std::endl;
    rptTxt_f << "                         Iterations : " << iterations << std::endl;
    rptTxt_f << "                          Host Name : " << hostName << std::endl;
    rptTxt_f << "                          User Name : " << userName << std::endl;
    rptTxt_f << "    Average Random Number Fill Time : " << FAvg_f << avgRandTime/iterations  << " secs." << std::endl;
    rptTxt_f << "     Average Host to Cuda Copy Time : " << FAvg_f << avgMemCpH2C/iterations  << " secs." << std::endl;
    rptTxt_f << "     Average Cuda to Host Copy Time : " << FAvg_f << avgMemCpC2H/iterations  << " secs." << std::endl;
    rptTxt_f << "       Average Matrix Multiply Time : " << FAvg_f << avgMmply/iterations << " secs." << std::endl;
    rptTxt_f << "                 Best Multiply Time : " << FAvg_f << minMmply << " secs." << std::endl;
    rptTxt_f << "      Total Time for all Iterations : " << FAvg_f << totTimeSecs << " secs." << std::endl;
    rptTxt_f << "---------------------------------------------------------------------------" << std::endl;
    rptTxt_f.close();
    return 0;
}

