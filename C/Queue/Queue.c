//-----------------------------------------------------------------------------
// Queue.c
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Queue.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node next;
} NodeObj;

// private QueueObj type
typedef struct QueueObj{
   Node front;
   Node back;
   int length;
} QueueObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newQueue()
// Returns reference to new empty Queue object.
Queue newQueue(){
   Queue Q;
   Q = malloc(sizeof(QueueObj));
   Q->front = Q->back = NULL;
   Q->length = 0;
   return(Q);
}

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeQueue(Queue* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
      while( !isEmpty(*pQ) ) { 
         Dequeue(*pQ); 
      }
      free(*pQ);
      *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
int getFront(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling getFront() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling getFront() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   return(Q->front->data);
}

// getLength()
// Returns the length of Q.
int getLength(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling getLength() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   return(Q->length);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
bool isEmpty(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling isEmpty() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   return(Q->length==0);
}


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data at the back of Q.
void Enqueue(Queue Q, int data)
{
   Node N = newNode(data);

   if( Q==NULL ){
      printf("Queue Error: calling Enqueue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   
   if( isEmpty(Q) ) { 
      Q->front = Q->back = N; 
   }else{ 
      Q->back->next = N; 
      Q->back = N; 
   }
   Q->length++;
}

// Dequeue()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)
void Dequeue(Queue Q){
   Node N = NULL;

   if( Q==NULL ){
      printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling Dequeue on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   N = Q->front;
   if( getLength(Q)>1 ) { 
      Q->front = Q->front->next; 
   }else{ 
      Q->front = Q->back = NULL; 
   }
   Q->length--;
   freeNode(&N);
}


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints a string representation of Q consisting of a space separated list 
// of ints to stdout.
void printQueue(Queue Q){
   Node N = NULL;

   if( Q==NULL ){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   for(N = Q->front; N != NULL; N = N->next){
      printf("%d ", N->data);
   }
   printf("\n");
}

// equals()
// Returns true (1) if A is same int sequence as B, false (0) otherwise.
bool equals(Queue A, Queue B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("Queue Error: calling equals() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}
