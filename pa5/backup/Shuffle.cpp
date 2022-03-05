#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

#include"List.h"

// This function alter its List& (List reference) argument D 
// by performing one shuffle operation, as described in pa5.pdf.
void shuffle(List& D);


int main(int argc, char * argv[]){

    ifstream in;
    ofstream out;
    stringstream ss;

    // ============================================================================= //
    // Step1: Check argument, open output\input file 
    // ============================================================================= //
    // Check command line for correct number of arguments
    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return(EXIT_FAILURE);
    }


    // ============================================================================= //
    // Step2: Print the result
    // ============================================================================= //
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    
    int deck;
    ss << argv[1];
    ss >> deck;

    List L;
    for(int i = 1; i <= deck; i++){
        // Generate a List
        // we can insert i into List L
        L.insertBefore(i-1);
        List D(L);

        // Perform shuffle list until it recovery to the origin order
        // and record shuffle count.
        int count = 0;
        do{
            shuffle(D);
            count ++;
        }while(! D.equals(L));

        // Print the sullfle count
        cout << i << "\t\t" << count << endl;
    }
    
    // ============================================================================= //
    // Step3: Close files and free memory
    // ============================================================================= //
    // Close files
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}

// TODO;
void shuffle(List& D){
    // cerr << "begin:" << D << endl;
    List temp;
    int split = D.length() / 2;
    D.moveFront();
    for(int i = 0; i < split; i++){
        int data = D.moveNext();
        temp.insertBefore(data);
        D.eraseBefore();
    }
    // cerr << "temp:" << temp << endl;
    // cerr << "mid" << D << endl;
    temp.moveFront();
    while(D.position() < D.length()){
        D.moveNext();
        if(temp.position() < temp.length()){
            D.insertAfter(temp.moveNext());
            D.moveNext();
        }

    }
    // cerr << "end:" << D << endl;
}