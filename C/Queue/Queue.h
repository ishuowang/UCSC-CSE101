//-----------------------------------------------------------------------------
// Queue.h
// Header file for Queue ADT
//-----------------------------------------------------------------------------
#ifndef QUEUE_H_INCLUDE_
#define QUEUE_H_INCLUDE_

#include<stdbool.h>


// Exported type --------------------------------------------------------------
typedef struct QueueObj* Queue;


// Constructors-Destructors ---------------------------------------------------

// newQueue()
// Returns reference to new empty Queue object. 
Queue newQueue();

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeQueue(Queue* pQ);


// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
int getFront(Queue Q);

// getLength()
// Returns the length of Q.
int getLength(Queue Q);

// isEmpty()
// Returns true if Q is empty, otherwise returns false.
bool isEmpty(Queue Q);


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data at the back of Q.
void Enqueue(Queue Q, int data);

// Dequeue()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)
void Dequeue(Queue Q);


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints a string representation of Q consisting of a space separated list 
// of ints to stdout.
void printQueue(Queue Q);

// equals()
// Returns true if A is same int sequence as B, false otherwise.
bool equals(Queue A, Queue B);

#endif
