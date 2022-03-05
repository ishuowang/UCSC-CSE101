//-----------------------------------------------------------------------------
//  BigIntegerTest.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

    BigInteger A = BigInteger("+111122223333");
    BigInteger B = BigInteger("-112122223333");
    BigInteger D = BigInteger("-1000000000");
    A += B;

    return EXIT_SUCCESS;
}

