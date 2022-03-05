//-----------------------------------------------------------------------------
// Stack.h
// Header file for Stack ADT
//-----------------------------------------------------------------------------
#ifndef STACK_H_INCLUDE_
#define STACK_H_INCLUDE_

#include<stdbool.h>


// Exported Type --------------------------------------------------------------
typedef struct StackObj* Stack;


// Constructors-Destructors ---------------------------------------------------

// newStack()
// Returns reference to new empty Stack object.
Stack newStack(void);

// freeStack()
// Frees all heap memory associated with Stack *pS, and sets *pS to NULL.
void freeStack(Stack* pS);


// Access functions -----------------------------------------------------------

// getTop()
// Returns the value at the top of S.
// Pre: !isEmpty(S)
int getTop(Stack S);

// getHeight()
// Returns the height of S.
int getHeight(Stack S);

// isEmpty()
// Returns true (1) if S is empty, otherwise returns false (0).
bool isEmpty(Stack S);


// Manipulation procedures ----------------------------------------------------

// push()
// Places new data element on top of S.
// Post: !isEmpty(S)
void push(Stack S, int data);

// pop()
// Deletes data element on top of S.
// Pre: !isEmpty(S)
void pop(Stack S);


// Other Functions ------------------------------------------------------------

// printStack()
// Prints a string representation of S consisting of a space separated list 
// of ints to stdout.
void printStack(Stack S);

// equals()
// Returns true (1) if A is same int sequence as B, false (0) otherwise.
bool equals(Stack A, Stack B);

#endif
