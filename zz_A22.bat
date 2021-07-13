:: SCRIPT A22 - CST8152 - S21
::
:: COMPILERS COURSE - SCRIPT ---------------------------------------------

SET COMPILER=zz_compiler.exe

REM ---------------------------------------------------------------------
REM - Begin of Tests (A22 - S21) ----------------------------------------
REM ---------------------------------------------------------------------

::
:: BASIC TESTS  ----------------------------------------------------------
::
REM - Basic Tests (A22 - S21) - - - - - - - - - - - - - - - - - - - - - -
ren *.exe %COMPILER%
%COMPILER% 1 input/a21_Empty.zz  	> output/a21_empty.out		2> output/a21_empty.err
%COMPILER% 1 input/a22_Numbers.zz	> output/a22_numbers.out	2> output/a22_numbers.err
%COMPILER% 1 input/a23_String.zz  	> output/a23_string.out 	2> output/a23_string.err
%COMPILER% 1 input/a24_General.zz  	> output/a24_general.out 	2> output/a24_general.err

REM ---------------------------------------------------------------------
REM - End of Tests (A22 - S21) ------------------------------------------
REM ---------------------------------------------------------------------
