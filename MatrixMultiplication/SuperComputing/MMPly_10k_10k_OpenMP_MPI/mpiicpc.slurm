#!/bin/bash -l
#SBATCH --job-name=hybrid
#SBATCH --time=4-00:00:00
#SBATCH --partition=parallel
#SBATCH --mem-per-cpu=1200
#SBATCH --nodes=4
#SBATCH --tasks-per-node=10
########################################################################################################################
DIR_PATH=/home/v_s191/MPI/V_04
ITERATIONS=25
NPROCS=40
MATRIX_SIZE=10000
HOST_NAME=`hostname -s`

LOG_FILE=Log_mpiicpc_$MATRIX_SIZE-$ITERATIONS-$NPROCS-$HOST_NAME.txt
COMP_FLAGS=" -qopenmp -O3 -xSSE4.2 -axCORE-AVX-I,CORE-AVX2 -static-intel" 
TARGET_BINARY=$DIR_PATH/mmpy_mpiicpc18_avx_sse

DRAW_LINE="echo -------------------------------------------------------------------------------------" >> $LOG_FILE

module load intel/18
export PATH=$PATH:/share/apps/intel/compilers_and_libraries_2018.0.128/linux/mpi/intel64/bin
cd $DIR_PATH
$DRAW_LINE  >> $LOG_FILE
cat $DIR_PATH/mpiicpc.slurm >> $LOG_FILE
$DRAW_LINE  >> $LOG_FILE

$DRAW_LINE  >> $LOG_FILE
echo "Compilation Started"  >> $LOG_FILE
COMPILE_CMD="/share/apps/intel/compilers_and_libraries_2018.0.128/linux/mpi/intel64/bin/mpiicpc  $COMP_FLAGS $DIR_PATH/MatrixMultiply.cpp -O3 -o $TARGET_BINARY"
echo $COMPILE_CMD >> $LOG_FILE
$COMPILE_CMD  >> $LOG_FILE
echo "Compilation Completed"  >> $LOG_FILE
$DRAW_LINE  >> $LOG_FILE


$DRAW_LINE  >> $LOG_FILE
EXEC_CMD="/share/apps/intel/compilers_and_libraries_2018.0.128/linux/mpi/intel64/bin/mpirun -np $NPROCS $TARGET_BINARY $MATRIX_SIZE $ITERATIONS  >> $LOG_FILE"
echo $EXEC_CMD  >> $LOG_FILE
$EXEC_CMD  >> $LOG_FILE
$DRAW_LINE  >> $LOG_FILE
module unload intel/18
exit 0

