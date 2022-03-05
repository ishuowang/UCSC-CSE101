#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------


Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c17 -Wall -c Lex.c

QuizClient: QuizClient.o List.o
	gcc -std=c17 -Wall -o QuizClient QuizClient.o List.o

QuizClient.o: QuizClient.c List.h
	gcc -std=c17 -Wall -c QuizClient.c

ListClient: ListClient.o List.o
	gcc -std=c17 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -std=c17 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o QuizClient.o QuizClient

checkClient : 
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --leak-check=full Lex in2 blah2


