//-----------------------------------------------------------------------------
// Stack.h
// Header file for Queue ADT
//-----------------------------------------------------------------------------
#include<string>
#include<iostream>

#ifndef STACK_H_INCLUDE_
#define STACK_H_INCLUDE_


// Exported type --------------------------------------------------------------
class Stack{

private:

   // private Node struct
   struct Node{
      // Node fields
      int data;
      Node* next;
      // Node constructor
      Node(int x);
   };

   // Stack fields
   Node* top;
   int height;

public:

   // Class Constructors & Destructors ----------------------------------------

   // Creates new Stack in the empty state.
   Stack();

   // Copy constructor.
   Stack(const Stack& L);

   // Destructor
   ~Stack();


   // Access functions --------------------------------------------------------

   // isEmpty()
   // Returns true if Stack is empty, otherwise returns false.
   int isEmpty();

   // getTop()
   // Returns the value at top of Stack.
   // Pre: !isEmpty()
   int getTop();

   // getHeight()
   // Returns the height of Stack.
   int getHeight();


   // Manipulation procedures -------------------------------------------------

   // push()
   // Places new data element on top of Stack.
   void push(int x);

   // pop()
   // Deletes data element on top of Stack.
   // Pre: !isEmpty()
   void pop();


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of Stack consisting of a space separated 
   // list of data values.
   std::string to_string();

   // equals()
   // Returns true if and only if this Stack is the same integer sequence as S.
   bool equals(const Stack& S);


   // Overriden Operators -----------------------------------------------------

   // operator<<()
   // Inserts string representation of S into stream.
   friend std::ostream& operator<<( std::ostream& stream, Stack& S );

   // operator==()
   // Returns true if and only if A is the same integer sequence as B.
   friend bool operator==( Stack& A, const Stack& B );

   // operator=()
   // Overwrites the state of this Stack with state of S.
   Stack& operator=( const Stack& S );

};


#endif
