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
ITERATIONS=100
MATRIX_SIZE=1000
HOST_NAME=`hostname -s`
EXEC_BIN_FILE=$DIR_PATH/regression/mmpy_icpc18


LOG_FILE=$DIR_PATH/regression/Log_icpc_$MATRIX_SIZE-$ITERATIONS-$HOST_NAME.txt

module load intel/18
cd $DIR_PATH/regression
echo icpc $DIR_PATH/MatrixMultiply.cpp -O3 -o $EXEC_BIN_FILE >> $LOG_FILE
icpc $DIR_PATH/MatrixMultiply.cpp -O3 -o $EXEC_BIN_FILE >> $LOG_FILE

########################################################################################################################
MATRIX_SIZE=100
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=200
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=400
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=600
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=800
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=1000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=2000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=4000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=5000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=6000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=7000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=8000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=9000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################

########################################################################################################################
MATRIX_SIZE=10000
echo $EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
$EXEC_BIN_FILE $MATRIX_SIZE $ITERATIONS >> $LOG_FILE
########################################################################################################################


cat $DIR_PATH/icpc.slurm >> $LOG_FILE
module unload intel/18
exit 0
