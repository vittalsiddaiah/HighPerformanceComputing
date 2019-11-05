## Building the source code
1. Download the above source code MatrixMultiply.cpp and StdHdr.hpp
2. Ensure to have the Intel® compiler enabled
3. 

```shell
module load intel/18
```

## Compilation of the program

```shell
/share/apps/intel/compilers_and_libraries_2018.0.128/linux/mpi/intel64/bin/mpiicpc  \
-qopenmp -O3 -xSSE4.2 -axCORE-AVX-I,CORE-AVX2 -static-intel /home/v_s191/MPI/V_04/MatrixMultiply.cpp \
-o /home/v_s191/MPI/V_04/mmpy_mpiicpc18_avx_sse
```

**Note:** Compiling the source on the target where the code would be executing has advantage(s):
The compiler has the idea fo the target system, 
- We have ***Broadwell*** ® systems in the compute-cluster and the compiler would generate a code that are optimized and an effective code is been generated.
- It is common that we compile on a host and execute on a cluster environment, mostly it should work. But there are times that if the cluster version (OS+Hardware) being different from the host version that you have compiled. In this situation, the binary fails to execute. Eg AVX instructions [Refer AVX](https://software.intel.com/en-us/articles/which-applications-are-most-likely-to-benefit-from-recompilation-for-intel-advanced-vector-extensions-intel-avx)

---


## Executing the binary
The above command should generate the binary in the **bin** folder

```shell
# The binary can be executed by:
# ./bin/mmpy_icpc18_avx  <Matrix Dimension> <number of iterations>
#/share/apps/intel/compilers_and_libraries_2018.0.128/linux/mpi/intel64/bin/mpirun  // MPIRun Binary
#-np <Number Of MPI-Processes> 
#/home/v_s191/MPI/V_04/mmpy_mpiicpc18_avx_sse <Size of Matrix> <Number of iterations per process>

/share/apps/intel/compilers_and_libraries_2018.0.128/linux/mpi/intel64/bin/mpirun \
-np 40 /home/v_s191/MPI/V_04/mmpy_mpiicpc18_avx_sse 10000 25 \
>> Log_mpiicpc_10000-25-40-compute-098.txt
```

> When running on Leap Severs, Copy the above file **icpc.slurm** and edit the file to change the directory path **DIR_PATH**
```shell
DIR_PATH=/home/v_s191/MPI/V_04
```
---


## Typical Output (On Screen Captured in )

```shell
cat ./slurm-94073.out 
/home/v_s191/MPI/V_04/MatrixMultiply.cpp(5): (col. 43) remark: main has been targeted for automatic cpu dispatch
icpc: warning #10237: -lcilkrts linked in dynamically, static library not available

******************************************* HomeWork : 4 *******************************************
*                                           Version 0.2                                            *
*                              EE 5321 CAE Simulation on HPC Systems                               *
*                        Contact: (Vittal) v_s191@txstate.edu  (A04848680)                         *
*                                      Texas State University                                      *
****************************************************************************************************

 Begining Rank 1
 Begining Rank 4
 Begining Rank 5
 Begining Rank 30
 Begining Rank 12
 Begining Rank 20
:
:
                    Matrix Size : 10000 x 10000
                     Iterations : 25
                      Host Name : compute-102.local
                      User Name : root
Average Random Number Fill Time :    4.50058 secs.
   Average Matrix Multiply Time :    72.9408 secs.
             Best Multiply Time :    72.8455 secs.
-----------------------------------------------------------------
The Following files were generated: 
 Report  File : ICPC_Report_30_20190309220031.csv
 Average File : ICPC_Average_30_20190309220031.csv
 Terminating Rank 30
-----------------------------------------------------------------
                    Matrix Size : 10000 x 10000
                     Iterations : 25
                      Host Name : compute-100.local
                      User Name : root
Average Random Number Fill Time :    5.07828 secs.
   Average Matrix Multiply Time :    72.8866 secs.
             Best Multiply Time :    72.2938 secs.
-----------------------------------------------------------------
The Following files were generated: 
 Report  File : ICPC_Report_10_20190309220031.csv
 Average File : ICPC_Average_10_20190309220031.csv
 Terminating Rank 10
                     Total time :    2018.77 secs.
-------------------------------------------------------------------------------------
```
# Benchmarks of the program


* Executed on the lab cluster (Leap) environment


```shell
-------------------------------------------------------------------------------------
                     Total time :    2018.77 secs. (~33 minutes 39 seconds)
-------------------------------------------------------------------------------------                     
```


The average log file for the 10000 x 10000 for 1000 iterations (**ICPC_Average_20190212212728.csv.gz**) is available at [OneDrive Click Here](https://onedrive.live.com/?id=EAB03D3DF0121AE7%21106&cid=EAB03D3DF0121AE7)  for accessing the same.

---

For further details, please contact:

- vittal.siddaiah@txstate.edu
- vittal.siddaiah@gmail.com

