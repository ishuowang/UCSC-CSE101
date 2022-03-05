#------------------------------------------------------------------------------
#  Makefile for Queue ADT
#
#  make             makes QueueTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

QueueTest : QueueTest.o Queue.o
	gcc -std=c17 -Wall -o QueueTest QueueTest.o Queue.o 

QueueTest.o : Queue.h QueueTest.c
	gcc -std=c17 -Wall -c QueueTest.c

Queue.o : Queue.h Queue.c
	gcc -std=c17 -Wall -c Queue.c

clean :
	rm -f QueueTest QueueTest.o Queue.o

check : 
	valgrind --leak-check=full QueueTest
