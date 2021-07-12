#!/bin/sh
COMPILER=./zz_compiler

#---------------------------------------------------------------------
#- Begin of Tests (A22 - S21) ----------------------------------------
#---------------------------------------------------------------------

##
## BASIC TESTS  ----------------------------------------------------------
##

# - Basic Tests (A22 - S21) - - - - - - - - - - - - - - - - - - - - - -
$COMPILER 1 input/a22_empty.zz  > output/a22_empty.out 2> output/a22_empty.err
$COMPILER 1 input/a22_Numbers.zz  > output/a22_Numbers.out 2> output/a22_Numbers.err
$COMPILER 1 input/a22_String.zz  > output/a22_String.out 2> output/a22_String.err
$COMPILER 1 input/a22_General.zz > output/a22_General.out 2> output/a22_General.err

# ---------------------------------------------------------------------
# - End of Tests (A12 - S21) ------------------------------------------
# ---------------------------------------------------------------------