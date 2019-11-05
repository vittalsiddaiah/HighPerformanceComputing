# Standalone version of matrix multiplication 10000 x 10000
## Building the source code
1. Download the above source code MatrixMultiply.cpp and StdHdr.hpp
2. Create a folder for binary 
```shell
mkdir ./bin
```
3. Ensure to have the Intel® compiler enabled

```shell
module load intel/18
```

# Compiling the program

```shell
icpc -O3 -xAVX -xSSE4.2 -axCORE-AVX-I,CORE-AVX2 MatrixMultiply.cpp -o ./bin/mmpy_icpc18_avx 
```

++**Note:**++ Compiling the source on the target where the code would be executing has advantage(s):
The compiler has the idea fo the target system, 
- We have ***Broadwell*** ® systems in the compute-cluster and the compiler would generate a code that are optimized and an effective code is been generated.
- It is common that we compile on a host and execute on a cluster environment, mostly it should work. But there are times that if the cluster version (OS+Hardware) being different from the host version that you have compiled. In this situation, the binary fails to execute. Eg AVX instructions [Refer AVX](https://software.intel.com/en-us/articles/which-applications-are-most-likely-to-benefit-from-recompilation-for-intel-advanced-vector-extensions-intel-avx)

Currently we are using limited options in compiler for optimization, The are several opportunities in exploring the plethora of compilation flags.  Refer to the ICC flags here [here](https://software.intel.com/en-us/articles/step-by-step-optimizing-with-intel-c-compiler)


---


## Executing the binary
The above command should generate the binary in the **bin** folder

```shell
# The binary can be executed by:
# ./bin/mmpy_icpc18_avx  <Matrix Dimension> <number of iterations>
./bin/mmpy_icpc18 10000 1000
```

---


## Typical Output

```shell
./mmpy_icpc18_avx 10000 100

******************************************* HomeWork : 2 *******************************************
*                                           Version 0.2                                            *
*                              EE 5321 CAE Simulation on HPC Systems                               *
*                        Contact: (Vittal) v_s191@txstate.edu  (A04848680)                         *
*                                      Texas State University                                      *
****************************************************************************************************
Assignment 02 Started
---------------------------------------------------
Iterations, RndTimeSecs, AvgRndTimeSecs, MplyTimeSecs, AvgMplyTimeSecs, MinMplyTime
      0001,    0.037499,       0.037499,     0.560613,        0.560613,    0.560613
      0002,    0.025432,      0.0314655,     0.390495,        0.475554,    0.390495
      0003,    0.025035,       0.029322,     0.295186,        0.415431,    0.295186
      0004,    0.018765,      0.0266828,      0.29376,        0.385013,     0.29376
      0005,    0.018778,      0.0251018,     0.293336,        0.366678,    0.293336
-----------------------------------------------------------------
                    Matrix Size : 10000 x 10000
                     Iterations : 1000
                      Host Name : compute-118.local
                      User Name : root
Average Random Number Fill Time :    1.46886 secs.
   Average Matrix Multiply Time :    121.518 secs.  
             Best Multiply Time :    120.534 secs.  
  Total Time for all Iterations :    129538  secs.  
-----------------------------------------------------------------
The Following files were generated: 
 Report  File : ICPC_Report_20190211151753.csv
 Average File : ICPC_Average_20190211151753.csv
-----------------------------------------------------------------
```

There are two output CSV files, The advantage of a CSV file format is that it is portable for other scripts to consume for next level of analytics.


1. **Report File** : Report file is in CSV Format, This would contain the following fields

```shell
1. MatrixSize,            # Matrix Size Eg. 10000 x 10000
2. Iterations,            # Number of Iterations Eg. 1000
3. HostName,              # Host Name on which the binary executed  Eg. compute-118.local
4. UserName,              # User Name who executed this Eg. v_s191
5. Avg RndTimeSecs,       # Average time taken to randomize the input Matrix in seconds.
6. AvgMultiplyTimeSecs,   # Average time taken to multiply two square matrix in seconds.
7. BestMultiplyTimeSecs,  # Best/Minimum time among the iterations in seconds.
8. TotalTimeSecs          # Total time to complete execution of the program in seconds.
```
```shell
MatrixSize, Iterations, HostName, UserName, Avg RndTimeSecs, AvgMultiplyTimeSecs, BestMultiplyTimeSecs, AvgTotalTimeSecs
1000, 5, login1.local, v_s191,  0.0251018,   0.366678,   0.293336,    2.66549
```

2. **Average File** : Average file would be the matrix averaging the product of all iterations.

```shell
# In this above example it would be [1000x1000] elements, all comma seprated
# Note the second column 
 1 36151.3, 38469, 151586, ...
 :
 :
 :
 999 104643, -21873.5, -78292.3, ...
1000 -121092, -48663.1, 24104.3, ...
```
# Benchmarks of the program
### prerequisite:
* Program has been compiled in Intel(®) C++ Compiler Version 18.
* -O3 is the only optimization being used.
* Executed on the lab cluster (Leap) environment

```shell
-----------------------------------------------------------------
                    Matrix Size : 10000 x 10000
                     Iterations : 10
                      Host Name : compute-118.local
                      User Name : root
Average Random Number Fill Time :    1.46886 secs.
   Average Matrix Multiply Time :    121.518 secs.  ~(2 mins 2 secs)
             Best Multiply Time :    120.534 secs.  ~(2 mins 1 secs)
  Total Time for all Iterations :    129538  secs.  ~(1.5 days)
-----------------------------------------------------------------

```


The average log file for the 10000 x 10000 for 1000 iterations is available at [OneDrive Click Here](https://onedrive.live.com/?id=EAB03D3DF0121AE7%21106&cid=EAB03D3DF0121AE7)  for accessing the same.

---

# Why ICC as compared to GCC
# Argument between float vs double

