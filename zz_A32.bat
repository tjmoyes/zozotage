:: SCRIPT A32 - CST8152 - S21
::
:: COMPILERS COURSE - SCRIPT ---------------------------------------------

SET COMPILER=zz_compiler.exe

SET FILE1=a31_Empty.zz
SET FILE2=a32_Hello.zz
SET FILE3=a33_Numbers.zz
SET FILE4=a34_General.zz


REM ---------------------------------------------------------------------
REM - Begin of Tests (A22 - S21) ----------------------------------------
REM ---------------------------------------------------------------------

::
:: BASIC TESTS  ----------------------------------------------------------
::
REM - Basic Tests (A32 - S21) - - - - - - - - - - - - - - - - - - - - - -
ren *.exe %COMPILER%
%COMPILER% 2 input/%FILE1%	> output/%FILE1%.out	2> output/%FILE1%.err
%COMPILER% 2 input/%FILE2%	> output/%FILE2%.out	2> output/%FILE2%.err
%COMPILER% 2 input/%FILE3%	> output/%FILE3%.out	2> output/%FILE3%.err
%COMPILER% 2 input/%FILE4%	> output/%FILE4%.out	2> output/%FILE4%.err

REM ---------------------------------------------------------------------
REM - End of Tests (A32 - S21) ------------------------------------------
REM ---------------------------------------------------------------------
