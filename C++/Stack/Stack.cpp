//-----------------------------------------------------------------------------
// Stack.cpp
// Implementation file for Stack ADT
//-----------------------------------------------------------------------------
#include<string>
#include<iostream>
#include"Stack.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node constructor
Stack::Node::Node(int x){
   data = x;
   next = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates new Stack in the empty state.
Stack::Stack(){
   top = nullptr;
   height = 0;
}

// Copy constructor.
Stack::Stack(const Stack& S){

   // make this an empty Stack
   top = nullptr;
   height = 0;

   // if S is non-empty, load its elements into this
   if( S.top!=nullptr ){
      Node* N = S.top;
      Node* M = new Node(N->data);
      top = M;
      while( N->next != nullptr ){
         N = N->next;
         M->next = new Node(N->data);
         M = M->next;
      }
      height = S.height;
   }
}

// Destructor
Stack::~Stack(){
   while( height>0 ){
      pop();
   }
}


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if Stack is empty, otherwise returns false.
int Stack::isEmpty(){
   return(height==0);
}

// getTop()
// Returns the value at top of Stack.
// Pre: !isEmpty()
int Stack::getTop(){
   if( isEmpty() ){
      cerr << "Stack Error: calling getTop() on an empty Stack" << endl;
      exit(EXIT_FAILURE);
   }
   return(top->data);
}

// getHeight()
// Returns the height of Stack.
int Stack::getHeight(){
   return(height);
}


// Manipulation procedures ----------------------------------------------------

// push()
// Places new data element on top of Stack.
void Stack::push(int x)
{
   Node* N = new Node(x);

   if( isEmpty() ) { 
      top = N; 
   }else{ 
      N->next = top;
      top = N;
   }
   height++;
}

// pop()
// Deletes data element on top of Stack.
// Pre: !isEmpty()
void Stack::pop(){
   if( isEmpty() ){
      cerr << "Stack Error: calling pop on an empty Stack" << endl;
      exit(EXIT_FAILURE);
   }
   
   Node* N = top;
   top = N->next;
   height--;
   delete N;
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of Stack consisting of a space separated 
// list of data values.
string Stack::to_string(){
   Node* N = nullptr;
   string s = "";

   for(N=top; N!=nullptr; N=N->next){
      s += std::to_string(N->data)+" ";
   }
   
   return s;
}

// equals()
// Returns true if and only if this Stack is the same integer sequence as S.
bool Stack::equals(const Stack& S){
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( this->height == S.height );
   N = this->top;
   M = S.top;
   while( eq && N!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of S into stream.
ostream& operator<< ( ostream& stream,  Stack& S ) {
   return stream << S.Stack::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B.
bool operator== (Stack& A, const Stack& B){
   return A.Stack::equals(B);
}

// operator=()
// Overwrites the state of this Stack with state of S.
Stack& Stack::operator=( const Stack& S ){
   if( this != &S ){ // not self assignment
      // make a copy of S
      Stack temp = S;

      // then swap the copy's fields with fields of this
      std::swap(top, temp.top);
      std::swap(height, temp.height);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return   
}
