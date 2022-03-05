#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
    //=============================================================================
    // Step1: Check argument, open output\input files.
    //=============================================================================
    ifstream in;
    ofstream out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // ============================================================================= //
    // Step2: Read BigInteger A and BigInteger B.
    // ============================================================================= //
    string line;
    getline(in, line);
    BigInteger A(line);
    getline(in, line);
    getline(in, line);
    BigInteger B(line);

    normalize(A);
    normalize(B);

    // ============================================================================= //
    // Step3: Perform arithmetic operation.
    // ============================================================================= //
    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A - B << endl << endl;
    out << A - A << endl << endl;
    out << A.mult(BigInteger("3")) - B.mult(BigInteger("2")) << endl << endl;
    out << A * B << endl << endl;
    out << A * A << endl << endl;
    out << B * B << endl << endl;
    out << (A * A * A * A).mult(BigInteger("9")) + (B * B * B * B * B).mult(BigInteger("16")) << endl << endl;

    // ============================================================================= //
    // Step3: Close opened files.
    // ============================================================================= //
    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
