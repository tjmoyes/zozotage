#!/bin/sh
COMPILER=./zz_compiler.exe

#---------------------------------------------------------------------
#- Begin of Tests (A12 - S21) ----------------------------------------
#---------------------------------------------------------------------

##
## BASIC TESTS  ----------------------------------------------------------
##

# - Basic Tests (A12 - S21) - - - - - - - - - - - - - - - - - - - - - -
$COMPILER 0 input/a12_empty.zz  > input/a12_empty.out 2> input/a12_empty.err
$COMPILER 0 input/a12_hello.zz  > input/a12_hello.out 2> input/a12_hello.err
$COMPILER 0 input/a12_maxfunction.zz  > input/a12_maxfunction.out 2> input/a12_maxfunction.err
$COMPILER 0 input/a12_empty.zz F 300 10 > input/a12_empty_F_300-10.out 2> input/a12_empty_F_300-10.err

##
## ADVANCED TESTS  -------------------------------------------------------
##

# - Advanced Tests (A12 - S21) - - - - - - - - -- - - - - - - - - - - -
$COMPILER 0 input/a12_big.zz  F 100 10 > input/a12_big-F-100-10.out 2> input/a12_big-F-100-10.err
$COMPILER 0 input/a12_big.zz  A 200 20 > input/a12_big-A-200-20.out 2> input/a12_big-A-200-20.err
$COMPILER 0 input/a12_big.zz  M 300 30 > input/a12_big-M-300-30.out 2> input/a12_big-M-300-30.err

# ---------------------------------------------------------------------
# - End of Tests (A12 - S21) ------------------------------------------
# ---------------------------------------------------------------------
