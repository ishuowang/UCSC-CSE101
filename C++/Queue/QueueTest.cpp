//-----------------------------------------------------------------------------
// QueueTest.cpp
// A test client for Queue ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"Queue.h"

using namespace std;

int main(){

   int i;
   Queue A;
   Queue B;

   for(i=1; i<=10; i++){
      A.Enqueue(i);
      B.Enqueue(11-i);
   }

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << endl;

   for(i=1; i<=6; i++){
      A.Enqueue(B.getFront());
      B.Dequeue();
   }
   Queue C = A;
   Queue D = A.join(B);

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << endl;
   
   cout << "A==A is " << (A==A?"true":"false") << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "A==C is " << (A==C?"true":"false") << endl;
   cout << endl;

   return(0);
}
