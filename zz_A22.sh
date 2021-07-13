#!/bin/sh
COMPILER=./zz_compiler

#---------------------------------------------------------------------
#- Begin of Tests (A22 - S21) ----------------------------------------
#---------------------------------------------------------------------

##
## BASIC TESTS  ----------------------------------------------------------
##

# - Basic Tests (A22 - S21) - - - - - - - - - - - - - - - - - - - - - -
$COMPILER 1 input/a21_empty.zz  > output/a21_empty.out 2> output/a21_empty.err
$COMPILER 1 input/a22_Numbers.zz  > output/a22_Numbers.out 2> output/a22_Numbers.err
$COMPILER 1 input/a23_String.zz  > output/a23_String.out 2> output/a23_String.err
$COMPILER 1 input/a24_General.zz > output/a24_General.out 2> output/a24_General.err

# ---------------------------------------------------------------------
# - End of Tests (A12 - S21) ------------------------------------------
# ---------------------------------------------------------------------