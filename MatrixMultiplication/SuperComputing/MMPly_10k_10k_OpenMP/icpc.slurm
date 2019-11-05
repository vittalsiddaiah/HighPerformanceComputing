#!/bin/bash -l
#SBATCH --job-name=mmp-10kOMP
#SBATCH --time=4-00:00:00
#SBATCH --partition=shared
#SBATCH --mem=64Gb
#SBATCH -n 28

########################################################################################################################
DIR_PATH=/home/v_s191/OMP/V_03
ITERATIONS=10
MATRIX_SIZE=10000
HOST_NAME=`hostname -s`

LOG_FILE=Log_icpc_$MATRIX_SIZE-$ITERATIONS-$HOST_NAME.txt
COMP_FLAGS=" -qopenmp -O3 -xAVX -xSSE4.2 -axCORE-AVX-I,CORE-AVX2 " 
TARGET_BINARY=$DIR_PATH/mmpy_icpc18_omp_avx_sse

DRAW_LINE="echo -------------------------------------------------------------------------------------" >> $LOG_FILE

module load intel/18
cd $DIR_PATH
$DRAW_LINE
cat $DIR_PATH/icpc.slurm >> $LOG_FILE

$DRAW_LINE
echo "Compilation Started"
COMPILE_CMD="icpc $COMP_FLAGS $DIR_PATH/MatrixMultiply.cpp -O3 -o $TARGET_BINARY"
echo $COMPILE_CMD
$COMPILE_CMD
echo "Compilation Completed"

$DRAW_LINE
EXEC_CMD="$TARGET_BINARY $MATRIX_SIZE $ITERATIONS >> $LOG_FILE"
echo $EXEC_CMD
$EXEC_CMD

$DRAW_LINE
module unload intel/18
exit 0
