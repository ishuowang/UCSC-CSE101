//-----------------------------------------------------------------------------
// StackTest.cpp
// A test client for Stack ADT
//-----------------------------------------------------------------------------
#include<string>
#include<iostream>
#include"Stack.h"

using namespace std;

int main(){

   int i;
   Stack A;
   Stack B;
   Stack C;

   for(i=1; i<=10; i++){
      A.push(i);
      B.push(11-i);
   }
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << endl;

   for(i=1; i<=6; i++){
      A.push(B.getTop());
      B.pop();
   }
   C = A;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;
   
   cout << "A==A is " << (A==A?"true":"false") << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "A==C is " << (A==C?"true":"false") << endl;
   cout << endl;

   return(0);
}
