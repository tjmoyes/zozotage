#!/bin/sh
# SCRIPT A32 - CST8152 - S21
# COMPILERS COURSE - SCRIPT ---------------------------------------------

COMPILER=./zz_compiler

FILE1=a31_Empty
FILE2=a32_Hello
FILE3=a33_Numbers


# ---------------------------------------------------------------------
# - Begin of Tests (A22 - S21) ----------------------------------------
# ---------------------------------------------------------------------

#
# BASIC TESTS  ----------------------------------------------------------
#
# - Basic Tests (A32 - S21) - - - - - - - - - - - - - - - - - - - - - -
$COMPILER 2 input/$FILE1.zz	> output/$FILE1.out	2> output/$FILE1.err
$COMPILER 2 input/$FILE2.zz	> output/$FILE2.out	2> output/$FILE2.err
$COMPILER 2 input/$FILE3.zz	> output/$FILE3.out	2> output/$FILE3.err

# ---------------------------------------------------------------------
# - End of Tests (A32 - S21) ------------------------------------------
# ---------------------------------------------------------------------