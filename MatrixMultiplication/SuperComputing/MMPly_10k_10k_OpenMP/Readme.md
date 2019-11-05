## Building the source code
1. Download the above source code MatrixMultiply.cpp and StdHdr.hpp
2. Ensure to have the Intel® compiler enabled

```shell
module load intel/18
```

# Compilation of the program

```shell
icpc -qopenmp -O3 -xSSE4.2 -axCORE-AVX-I,CORE-AVX2 -static-intel /home/v_s191/OMP/V_04/MatrixMultiply.cpp -O3 -o /home/v_s191/OMP/V_04/mmpy_icpc18_omp_avx_sse
```

**Note:** Compiling the source on the target where the code would be executing has advantage(s):
The compiler has the idea fo the target system, 
- We have ***Broadwell*** ® systems in the compute-cluster and the compiler would generate a code that are optimized and an effective code is been generated.
- It is common that we compile on a host and execute on a cluster environment, mostly it should work. But there are times that if the cluster version (OS+Hardware) being different from the host version that you have compiled. In this situation, the binary fails to execute. Eg AVX instructions [Refer AVX](https://software.intel.com/en-us/articles/which-applications-are-most-likely-to-benefit-from-recompilation-for-intel-advanced-vector-extensions-intel-avx)

---


## Executing the binary (*Standalone Mode*)
The above command should generate the binary in the **bin** folder

```shell
# The binary can be executed by:
# ./bin/mmpy_icpc18_avx  <Matrix Dimension> <number of iterations>
./mmpy_icpc18_omp_avx_sse 10000 1000
```

> When running on Leap Severs, Copy the above file **icpc.slurm** and edit the file to change the directory path **DIR_PATH**
```shell
DIR_PATH=/home/v_s191/OMP/V_03
```
---


## Typical Output (On Screen Captured in )

```shell
cat ./slurm-84033.out
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
Compilation Started
icpc -qopenmp -O3 -xSSE4.2 -axCORE-AVX-I,CORE-AVX2 -static-intel /home/v_s191/OMP/V_04/MatrixMultiply.cpp -O3 -o /home/v_s191/OMP/V_04/mmpy_icpc18_omp_avx_sse
/home/v_s191/OMP/V_04/MatrixMultiply.cpp(4): (col. 43) remark: main has been targeted for automatic cpu dispatch
icpc: warning #10237: -lcilkrts linked in dynamically, static library not available
Compilation Completed
-------------------------------------------------------------------------------------
/home/v_s191/OMP/V_04/mmpy_icpc18_omp_avx_sse 10000 1000 >> Log_icpc_10000-1000-compute-046.txt
******************************************* HomeWork : 3 *******************************************
*                                           Version 0.4                                            *
*                              EE 5321 CAE Simulation on HPC Systems                               *
*                        Contact: (Vittal) v_s191@txstate.edu  (A04848680)                         *
*                                      Texas State University                                      *
****************************************************************************************************

Iterations, RndTimeSecs, AvgRndTimeSecs, MplyTimeSecs, AvgMplyTimeSecs, MinMplyTime
      0001,     1.70813,        1.70813,      7.15667,         7.15667,     7.15667
      0002,     3.46605,        2.58709,      7.28678,         7.22172,     7.15667
      0003,     3.84985,        3.00801,      7.05854,         7.16733,     7.05854
      0004,     4.43446,        3.36462,      6.05103,         6.88825,     6.05103
      0005,     3.65134,        3.42197,      5.94944,         6.70049,     5.94944
      0006,     4.38236,        3.58203,      6.03032,         6.58879,     5.94944
      0007,     3.65347,        3.59224,      5.97701,          6.5014,     5.94944
      0008,     4.35519,        3.68761,      6.01381,         6.44045,     5.94944
      0009,     3.65426,         3.6839,      5.96638,         6.38777,     5.94944
      0010,       4.355,        3.75101,      5.95418,         6.34441,     5.94944
      0011,     3.65528,        3.74231,      5.93437,         6.30714,     5.93437
      0012,     4.39657,        3.79683,      6.04462,         6.28526,     5.93437
      0013,     3.66597,        3.78676,      5.94482,         6.25907,     5.93437
      0014,     4.35488,        3.82734,      6.03133,         6.24281,     5.93437
      0015,     3.67038,        3.81688,      5.96518,          6.2243,     5.93437
      0016,     4.34366,         3.8498,      5.95795,         6.20765,     5.93437
      0017,     3.66767,        3.83909,      5.93836,         6.19181,     5.93437
      0018,     4.40195,        3.87036,      6.04432,         6.18362,     5.93437
      0019,     3.66131,        3.85936,      5.96948,         6.17235,     5.93437
      0020,     4.35791,        3.88428,      6.01566,         6.16451,     5.93437
      0021,     3.65504,        3.87337,      5.96447,         6.15499,     5.93437
:
:
:

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
$ cat ./ICPC_Report_20190212212728.csv
MatrixSize, Iterations, HostName, UserName, AvgRndTimeSecs, AvgMultiplyTimeSecs, BestMultiplyTimeSecs, TotalTimeSecs
10000, 1000, root, compute-107.local,   0.147722,     5.2937,     5.0966,    5482.02
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
* Optimization Flags are:  
```shell
           -qopenmp -O3 -xSSE4.2 -axCORE-AVX-I,CORE-AVX2 -static-intel
```

* Executed on the lab cluster (Leap) environment


```shell
-----------------------------------------------------------------
                    Matrix Size : 10000 x 10000
                     Iterations : 1000
                      Host Name : compute-107.local
                      User Name : root
Average Random Number Fill Time :    0.1477 secs.
   Average Matrix Multiply Time :    5.2937 secs.  
             Best Multiply Time :    5.0966 secs.  
  Total Time for all Iterations :   5482.02 secs. ~(1hr 31mins 22secs)
-----------------------------------------------------------------
The Following files were generated: 
 Report  File : ICPC_Report_20190212212728.csv
 Average File : ICPC_Average_20190212212728.csv
-----------------------------------------------------------------
```


The average log file for the 10000 x 10000 for 1000 iterations (**ICPC_Average_20190212212728.csv.gz**) is available at [OneDrive Click Here](https://onedrive.live.com/?id=EAB03D3DF0121AE7%21106&cid=EAB03D3DF0121AE7)  for accessing the same.

---

For further details, please contact:

- vittal.siddaiah@txstate.edu
- vittal.siddaiah@gmail.com

