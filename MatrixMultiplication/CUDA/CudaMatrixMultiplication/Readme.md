## Building the source code
1. Download the above source code mmply.cu and StdHdr.hpp

## Compilation of the program
```shell
nvcc --std=c++11 -arch=sm_70 ./MatrixMultiplyCuda.cu -o ./cuda_mmply
```
---


## Executing the binary
The above command should generate the binary in the **bin** folder

```shell
# The binary can be executed by:
# .cuda_mmply  <Matrix Dimension> <number of iterations>
./cuda_mmply 2000 50 > CudaMatrixMultiply.csv
```
---


## Typical Output (On Screen Captured in )

```shell
cat CudaMatrixMultiply.csv 
******************************************* HomeWork : 5 *******************************************
*                                     Version 0.4 (CUDA Programming)                               *
*                              EE 5321 CAE Simulation on HPC Systems                               *
*                        Contact: (Vittal) v_s191@txstate.edu  (A04848680)                         *
*                                      Texas State University                                      *
****************************************************************************************************

  HostRand,AvgHostRand,   MemcpH2C,AvgMemcpH2C,  MMPlyCuda,AvgMMPlyCuda,MinMMPlyCuda,  MemcpC2H,AvgMemcpC2H
  0.184317,   0.184317,     0.0035,     0.0035,    1.3e-05,    1.3e-05,    1.3e-05,   0.020074,   0.020074, 
  0.181009,   0.182663,   0.003472,   0.003486,      3e-06,      8e-06,      3e-06,   0.016171,  0.0181225, 
  0.181005,    0.18211,   0.003463, 0.00347833,      3e-06, 6.33333e-06,      3e-06,   0.016282,   0.017509, 
  0.181019,   0.181837,   0.003481,   0.003479,      3e-06,    5.5e-06,      3e-06,   0.016198,  0.0171812, 
  0.181166,   0.181703,   0.003483,  0.0034798,      3e-06,      5e-06,      3e-06,   0.016165,   0.016978, 
  0.181029,   0.181591,   0.003485, 0.00348067,      3e-06, 4.66667e-06,      3e-06,   0.016158,  0.0168413, 
  0.180884,    0.18149,   0.003474, 0.00347971,      4e-06, 4.57143e-06,      3e-06,   0.016172,  0.0167457, 
  0.182216,   0.181581,    0.00413,   0.003561,      4e-06,    4.5e-06,      3e-06,   0.016489,  0.0167136, 
  0.181132,   0.181531,   0.003482, 0.00355222,      3e-06, 4.33333e-06,      3e-06,   0.016164,  0.0166526, 
  0.181045,   0.181482,   0.003488,  0.0035458,      4e-06,    4.3e-06,      3e-06,   0.016161,  0.0166034, 
  0.181239,    0.18146,   0.003474, 0.00353927,      3e-06, 4.18182e-06,      3e-06,   0.016159,   0.016563, 
  0.180954,   0.181418,   0.003476,   0.003534,      3e-06, 4.08333e-06,      3e-06,   0.016168,  0.0165301, 
  0.180971,   0.181384,   0.003592, 0.00353846,      4e-06, 4.07692e-06,      3e-06,   0.016163,  0.0165018, 
  0.180984,   0.181355,   0.003478, 0.00353414,      3e-06,      4e-06,      3e-06,   0.016165,  0.0164778, 
  0.180933,   0.181327,   0.003472,    0.00353,      3e-06, 3.93333e-06,      3e-06,   0.016187,  0.0164584, 
  0.181518,   0.181339,   0.003498,   0.003528,      4e-06, 3.9375e-06,      3e-06,   0.016169,  0.0164403, 
  0.180932,   0.181315,   0.003464, 0.00352424,      2e-06, 3.82353e-06,      2e-06,   0.016177,  0.0164248, 
  0.181225,    0.18131,   0.003483, 0.00352194,      7e-06,      4e-06,      2e-06,    0.01616,  0.0164101, 
  0.181149,   0.181203,    0.00348,   0.003518,      3e-06, 3.63636e-06,      2e-06,   0.016169,  0.0163118, 
:
```
# Benchmarks of the program

```shell
-----------------   Cuda Matrix Multiplication Score Card -----------------
                        Matrix Size : 2000 x 2000
                         Iterations : 50
                          Host Name : hipe2
                          User Name : v_s191
    Average Random Number Fill Time :   0.181165 secs.
     Average Host to Cuda Copy Time :  0.0035149 secs.
     Average Cuda to Host Copy Time :  0.0162701 secs.
       Average Matrix Multiply Time :   3.46e-06 secs.
                 Best Multiply Time :      2e-06 secs.
      Total Time for all Iterations :    11.6583 secs.
---------------------------------------------------------------------------
```


The average log file for the 2000 x 2000 for 50 iterations ./CudaAverageMatrixFile.dat.gz 

---

For further details, please contact:

- vittal.siddaiah@txstate.edu
- vittal.siddaiah@gmail.com

