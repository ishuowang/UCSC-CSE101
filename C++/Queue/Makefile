#------------------------------------------------------------------------------
#  Makefile for Queue ADT
#
#  make             makes QueueTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

COMPILE          = g++ -std=c++17 -Wall -c 
LINK             = g++ -std=c++17 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full

QueueTest : QueueTest.o Queue.o
	$(LINK) QueueTest QueueTest.o Queue.o 

QueueTest.o : Queue.h QueueTest.cpp
	$(COMPILE) QueueTest.cpp

Queue.o : Queue.h Queue.cpp
	$(COMPILE) Queue.cpp

clean :
	$(REMOVE) QueueTest QueueTest.o Queue.o

check : QueueTest
	$(MEMCHECK) QueueTest
