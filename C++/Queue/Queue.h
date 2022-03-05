//-----------------------------------------------------------------------------
// Queue.h
// Header file for Queue ADT
//-----------------------------------------------------------------------------
#include<string>
#include<iostream>

#ifndef QUEUE_H_INCLUDE_
#define QUEUE_H_INCLUDE_


// Exported type --------------------------------------------------------------
class Queue{

private:

   // private Node struct
   struct Node{
      // Node fields
      int data;
      Node* next;
      // Node constructor
      Node(int x);
   };

   // Queue fields
   Node* front;
   Node* back;
   int length;

public:
   
   // Class Constructors & Destructors ----------------------------------------

   // Creates a new Queue in the empty state.
   Queue();

   // Copy Constructor.
   Queue(const Queue& Q);

   // Destructor
   ~Queue();


   // Access functions --------------------------------------------------------

   // isEmpty()
   // Returns true if Queue is empty, otherwise returns false.
   int isEmpty();

   // getFront()
   // Returns the value at the front of Queue.
   // Pre: !isEmpty()
   int getFront();

   // getLength()
   // Returns the length of Queue.
   int getLength();


   // Manipulation procedures -------------------------------------------------

   // Enqueue()
   // Inserts new data at back of Queue.
   void Enqueue(int x);

   // Dequeue()
   // Deletes element at front of Queue.
   // Pre: !isEmpty()
   void Dequeue();

   // join()
   // Returns a new Queue consisting of the elements of this Queue, followed
   // the elements of Q.
   Queue join(const Queue& Q);

   // Other Functions ---------------------------------------------------------

   // toString()
   // Returns a string representation of Queue consisting of a space separated 
   // list of data values.
   std::string to_string();

   // equals()
   // Returns true if and only if this is the same integer sequence as Q.
   bool equals(const Queue& Q);


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Q into stream.
   friend std::ostream& operator<<( std::ostream& stream, Queue& Q );

   // operator==()
   // Returns true if and only if A is the same integer sequence as B.
   friend bool operator==( Queue& A, const Queue& B );

   // operator=()
   // Overwrites the state of this Queue with state of Q.
   Queue& operator=( const Queue& Q );

};


#endif
