# zozotage
A Lisp-like compiler that allows users to code in French

# A12 README
* Bat (OPTIONAL):
	- Contains test scripts
	- This batch is optional but you need to provide a way to describe your execution (ex: what are your inputs, how to generate outputs, etc.)

* Code (REQUIRED):
	- Contains code needed to make the Buffer
	- Change Buffer.h and Buffer.c according to language.
	- DO NOT TOUCH (used for evaluation):
    	- Compilers.c
    	- Compilers.h
    	- MainBuffer.c

* Input (REQUIRED):
	- Contains example source code to test Buffer
	- Must have:
		+ Blank file with no chars
		+ Hello world
		+ A program that does anything
		+ A huge file that's a lot of characters long, almost as large as language's MAX_INT
    		+ e.g. printing a very long string
