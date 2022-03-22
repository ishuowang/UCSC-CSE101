#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){
    //============================================================================= //
    // Step1: Check argument, open output\input files.
    //============================================================================= //
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
    // Step2: Read Dictionary D from infile.
    // ============================================================================= //
    string line;
    Dictionary D;
    for(int i = 1; getline(in, line); i++){
        D.setValue(line, i);
    }

    // ============================================================================= //
    // Step3: Write D to outfile.
    // ============================================================================= //
    out << D.to_string() << endl;
    out << D.pre_string() << endl;

    // ============================================================================= //
    // Step3: Close file pointers.
    // ============================================================================= //
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
