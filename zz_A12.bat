:: SCRIPT A12 - CST8152 - S21
::
:: COMPILERS COURSE - SCRIPT ---------------------------------------------


SET COMPILER=zz_compiler.exe

REM ---------------------------------------------------------------------
REM - Begin of Tests (A12 - S21) ----------------------------------------
REM ---------------------------------------------------------------------

::
:: BASIC TESTS  ----------------------------------------------------------
::
REM - Basic Tests (A12 - S21) - - - - - - - - - - - - - - - - - - - - - -
%COMPILER% 0 input/a12_empty.zz  > input/a12_empty.out 2> input/a12_empty.err
%COMPILER% 0 input/a12_hello.zz  > input/a12_hello.out 2> input/a12_hello.err
%COMPILER% 0 input/a12_maxfunction.zz  > input/a12_maxfunction.out 2> input/a12_maxfunction.err

::
:: ADVANCED TESTS  -------------------------------------------------------
::
REM - Advanced Tests (A12 - S21) - - - - - - - - -- - - - - - - - - - - -
%COMPILER% 0 input/a12_lorem.zz  F 100 10 > input/a12_lorem-F-100-10.out 2> input/a12_lorem-F-100-10.err
%COMPILER% 0 input/a12_lorem.zz  A 200 20 > input/a12_lorem-A-200-20.out 2> input/a12_lorem-A-200-20.err
%COMPILER% 0 input/a12_lorem.zz  M 300 30 > input/a12_lorem-M-300-30.out 2> input/a12_lorem-M-300-30.err

REM ---------------------------------------------------------------------
REM - End of Tests (A12 - S21) ------------------------------------------
REM ---------------------------------------------------------------------
