//-----------------------------------------------------------------------------
// Queue.cpp
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"Queue.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node constructor
Queue::Node::Node(int x){
   data = x;
   next = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
Queue::Queue(){
   front = nullptr;
   back = nullptr;
   length = 0;
}

// Copy Constructor.
Queue::Queue(const Queue& Q){
   // make this an empty Queue
   front = nullptr;
   back = nullptr;
   length = 0;

   // load elements of Q into this
   Node* N = Q.front;
   while( N!=nullptr ){
      this->Enqueue(N->data);
      N = N->next;
   }
}

// Destructor
Queue::~Queue(){
   while( length>0 ){
      Dequeue();
   }
}


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if Queue is empty, otherwise returns false.
int Queue::isEmpty(){
   return(length==0);
}

// getFront()
// Returns the value at the front of Queue.
// Pre: !isEmpty()
int Queue::getFront(){
   if( isEmpty() ){
      cerr << "Queue Error: calling getFront() on an empty Queue" << endl;
      exit(EXIT_FAILURE);
   }
   return(front->data);
}

// getLength()
// Returns the length of Queue.
int Queue::getLength(){
   return(length);
}


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Inserts new data at back of Queue.
void Queue::Enqueue(int x)
{
   Node* N = new Node(x);

   if( isEmpty() ) { 
      front = back = N; 
   }else{ 
      back->next = N; 
      back = N; 
   }
   length++;
}

// Dequeue()
// Deletes data at back of Queue
// Pre: !isEmpty()
void Queue::Dequeue(){

   if( length==0 ){
      cerr << "Queue Error: calling Dequeue on an empty Queue" << endl;
      exit(EXIT_FAILURE);
   }
   
   Node* N = front;
   if( length>1 ) { 
      front = front->next; 
   }else{ 
      front = back = nullptr; 
   }
   length--;
   delete N;
}

// join()
// Returns a new Queue consisting of the elements of this Queue, followed
// the elements of Q.
Queue Queue::join(const Queue& Q){
   Queue J;
   Node* N = this->front;
   Node* M = Q.front;
   while( N!=nullptr ){
      J.Enqueue(N->data);
      N = N->next;
   }
   while( M!=nullptr ){
      J.Enqueue(M->data);
      M = M->next;
   }
   return J;
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of Queue consisting of a space separated 
// list of data values.
string Queue::to_string(){
   Node* N = nullptr;
   string s = "";

   for(N=front; N!=nullptr; N=N->next){
      s += std::to_string(N->data)+" ";
   }
   
   return s;
}

// equals()
// Returns true if and only if this is the same integer sequence as Q.
bool Queue::equals(const Queue& Q){
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( this->length == Q.length );
   N = this->front;
   M = Q.front;
   while( eq && N!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of Q into stream.
ostream& operator<< ( ostream& stream,  Queue& Q ) {
   return stream << Q.Queue::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B.
bool operator== (Queue& A, const Queue& B){
   return A.Queue::equals(B);
}

// operator=()
// Overwrites the state of this Queue with state of Q.
Queue& Queue::operator=( const Queue& Q ) {
   if( this != &Q ){ // not self assignment
      // make a copy of Q
      Queue temp = Q;

      // then swap the copy's fields with fields of this
      std::swap(front, temp.front);
      std::swap(back, temp.back);
      std::swap(length, temp.length);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}
