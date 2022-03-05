#------------------------------------------------------------------------------
#  Makefile for Stack ADT
#
#  make             makes StackTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

COMPILE          = g++ -std=c++17 -Wall -c 
LINK             = g++ -std=c++17 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full

StackTest : StackTest.o Stack.o
	$(LINK) StackTest StackTest.o Stack.o 

StackTest.o : Stack.h StackTest.cpp
	$(COMPILE) StackTest.cpp

Stack.o : Stack.h Stack.cpp
	$(COMPILE) Stack.cpp

clean :
	$(REMOVE) StackTest StackTest.o Stack.o

check : StackTest
	$(MEMCHECK) StackTest
