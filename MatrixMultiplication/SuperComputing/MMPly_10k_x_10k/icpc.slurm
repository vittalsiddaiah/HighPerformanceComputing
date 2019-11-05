#!/bin/bash -l
#SBATCH --job-name=mmp-10kx1k
#SBATCH --time=4-00:00:00
#SBATCH --partition=shared
#SBATCH --mem=64Gb
#SBATCH -n 28
#SBATCH --mail-user=v_s191@txstate.edu
#SBATCH --mail-type=end,begin

########################################################################################################################
DIR_PATH=/home/v_s191/homework/02
ITERATIONS=1000
MATRIX_SIZE=10000
HOST_NAME=`hostname -s`

LOG_FILE=Log_icpc_$MATRIX_SIZE-$ITERATIONS-$HOST_NAME.txt

module load intel/18
cd $DIR_PATH
echo icpc $DIR_PATH/MatrixMultiply.cpp -O3 -o $DIR_PATH/mmpy_icpc18 >> $LOG_FILE
icpc $DIR_PATH/MatrixMultiply.cpp -O3 -o $DIR_PATH/mmpy_icpc18 >> $LOG_FILE
echo $DIR_PATH/mmpy_icpc18 $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$DIR_PATH/mmpy_icpc18 $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
cat $DIR_PATH/icpc.slurm >> $LOG_FILE
module unload intel/18
exit 0
