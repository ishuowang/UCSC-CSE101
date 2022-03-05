//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   // std::string ideal = "a : 1\nb : 5\ne : 10\nf : 20\nh : 15\ni : 100\n";
   Dictionary A;
   // A.setValue("a", 1);
   // A.setValue("b", 5);
   // A.setValue("e", 10);
   // A.setValue("h", 15);
   // A.setValue("f", 20);
   // A.setValue("i", 100);
   // std::string val = A.to_string();
   // std::cout << val;
   // std::cout << ideal;
   // std::cout << val.length() << "\t" << ideal.length();
   // if (ideal != val){
   //    std::cout << "not equal" << std::endl;
   // }else{
   //    std::cout << "equal" << std::endl;
   // }

   std::string ideal = "a\nb\ne\nh\nf\ni\n";
   A.setValue("a", 1);
   A.setValue("b", 5);
   A.setValue("e", 10);
   A.setValue("h", 15);
   A.setValue("f", 20);
   A.setValue("i", 100);
   std::string val = A.pre_string();
   std::cout << val;
   std::cout << "===" << std::endl;
   std::cout << ideal;
   std::cout << val.length() << "\t" << ideal.length() << std::endl;
   if (val != ideal){
      std::cout << "not equal" << endl;
   }
   return( EXIT_SUCCESS );
}
