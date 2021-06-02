:: SCRIPT A12 - CST8152 - S21
::
:: COMPILERS COURSE - SCRIPT ---------------------------------------------

:: TODO: CHANGE THE NAME OF BINARY AND INPUTS / OUTPUTS / ERROR FILES

SET COMPILER=Compilers.exe

REM ---------------------------------------------------------------------
REM - Begin of Tests (A12 - S21) ----------------------------------------
REM ---------------------------------------------------------------------

::
:: BASIC TESTS  ----------------------------------------------------------
::
REM - Basic Tests (A12 - S21) - - - - - - - - - - - - - - - - - - - - - -
%COMPILER% 0 a12_empty.sof  > a12_empty.out 2> a12_empty.err
%COMPILER% 0 a12_hello.sof  > a12_hello.out 2> a12_hello.err
%COMPILER% 0 a12_basic.sof  > a12_basic.out 2> a12_basic.err

::
:: ADVANCED TESTS  -------------------------------------------------------
::
REM - Advanced Tests (A12 - S21) - - - - - - - - -- - - - - - - - - - - -
%COMPILER% 0 a12_lorem.sof  F 100 10 > a12_lorem-F-100-10.out 2> a12_lorem-F-100-10.err
%COMPILER% 0 a12_lorem.sof  A 200 20 > a12_lorem-A-200-20.out 2> a12_lorem-A-200-20.err
%COMPILER% 0 a12_lorem.sof  M 300 30 > a12_lorem-M-300-30.out 2> a12_lorem-M-300-30.err

REM ---------------------------------------------------------------------
REM - End of Tests (A12 - S21) ------------------------------------------
REM ---------------------------------------------------------------------
