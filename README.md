# zozotage
A Lisp-like compiler that allows users to code in French

# A12 Test
* To test the buffer, run either zz_A12.bat or zz_A12.sh depending on platform, and check the output folder for the .out and .err files
## Who did what - A12
Jon Liu
* Reworked header file
* Wrote makefile and build system

Tyson Moyes
* Testing script authored for Linux and tested
* Testing script for Windows tested
* Wrote makefile and build system

# A22 Test
* To test the scanner, run either zz_A22.bat or zz_A22.sh depending on platform, and check the output folder for the .out and .err files
## Who did what - A22
Jon Liu
* Edited a22_Numbers.zz to more properly match language style
* Adjusted types
* Implemented transition table
* Finished accepting state functions
* Generally helped implement functionality

Tyson Moyes
* Authored a22_Numbers.zz and a22_String.zz for testing
* Wrote code for Tokenizer
* Edited Makefile
* Edited testing script for Linux and Windows
* Generally helped implement functionality

# A32 Test
* Parser is not fully functional. You can run either zz_A32.bat or zz_A32.sh, and check the output but it is broken. 



# NOTE
* If recompiling, MainBuffer.c throws a warning about expecting a long unsigned int but receiving a type 'zz_int'; we are instructed not to change MainBuffer.c, however, so it shall remain. 

```bash
code/MainBuffer.c: In function ‘displayBuffer’:
code/MainBuffer.c:201:52: warning: format ‘%lu’ expects argument of type ‘long unsigned int’, but argument 2 has type ‘zz_int’ {aka ‘int’} [-Wformat=]
```

* There is currently a bug with the ~ character not properly being parsed, leading to an infinite loop when reading a24_General. We were not able to resolve this bug in time for A22 submission. This bug may also cause an infinite loop from the script (it does on Linux as far as I can tell - TM), so you may need to control C after a couple of seconds. 
