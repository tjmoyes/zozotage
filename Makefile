OBJS = Compilers.o Buffer.o MainBuffer.o
CFLAGS = -g -Wall -Wextra -ansi -pedantic
CC = cc

zz_compiler : $(OBJS)
	$(CC) $(OBJS) -o zz_compiler.exe

asan : $(OBJS)
	$(CC) -o zz_compiler.exe $(OBJS) -fsanitize=address -lasan

Buffer.o : code/Buffer.c code/Buffer.h code/Compilers.h
	$(CC) -o Buffer.o -c code/Buffer.c
Compilers.o : code/Compilers.c code/Compilers.h
	$(CC) -o Compilers.o -c code/Compilers.c
MainBuffer.o : code/MainBuffer.c code/Buffer.h
	$(CC) -o MainBuffer.o -c code/MainBuffer.c

.PHONY : clean
clean:
	-rm zz_compiler.exe $(OBJS)