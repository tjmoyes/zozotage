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



# NOTE
If recompiling, MainBuffer.c throws a warning about expecting a long unsigned int but receiving a type 'zz_int'; we are instructed not to change MainBuffer.c, however, so it shall remain. 

```bash
code/MainBuffer.c: In function ‘displayBuffer’:
code/MainBuffer.c:201:52: warning: format ‘%lu’ expects argument of type ‘long unsigned int’, but argument 2 has type ‘zz_int’ {aka ‘int’} [-Wformat=]
```