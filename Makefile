# MAKEFILE for Zozotage compiler
# Authors: Jon Liu 040967432, Tyson Moyes 040761903
# Course: CST 8152 - Compilers, Lab Section: 013
# Purpose: Create the executable for the compiler

OBJS = Compilers.o Buffer.o MainBuffer.o Scanner.o MainScanner.o
CFLAGS = -g -Wall -Wextra -ansi -pedantic
CC = cc

zz_compiler : $(OBJS)
	$(CC) $(OBJS) -o zz_compiler

asan : $(OBJS)
	$(CC) -o zz_compiler.exe $(OBJS) -fsanitize=address -lasan

Buffer.o : code/Buffer.c code/Buffer.h code/Compilers.h
	$(CC) -o Buffer.o -c code/Buffer.c
Compilers.o : code/Compilers.c code/Compilers.h
	$(CC) -o Compilers.o -c code/Compilers.c
MainBuffer.o : code/MainBuffer.c code/Buffer.h
	$(CC) -o MainBuffer.o -c code/MainBuffer.c
Scanner.o : code/Scanner.c code/Scanner.h code/Compilers.h
	$(CC) -o Scanner.o -c code/Scanner.c
MainScanner.o : code/MainScanner.c code/Scanner.h code/Buffer.h
	$(CC) -o MainScanner.o -c code/MainScanner.c

.PHONY : clean
clean:
	-rm zz_compiler $(OBJS) output/*