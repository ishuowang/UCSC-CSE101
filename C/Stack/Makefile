#------------------------------------------------------------------------------
#  Makefile for Stack ADT
#
#  make             makes StackTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

StackTest : StackTest.o Stack.o
	gcc -std=c17 -Wall -o StackTest StackTest.o Stack.o 

StackTest.o : Stack.h StackTest.c
	gcc -std=c17 -Wall -c StackTest.c

Stack.o : Stack.h Stack.c
	gcc -std=c17 -Wall -c Stack.c

clean :
	rm -f StackTest StackTest.o Stack.o

check : 
	valgrind --leak-check=full StackTest
