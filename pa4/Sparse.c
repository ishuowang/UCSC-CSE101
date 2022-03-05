#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"Matrix.h"
#include"List.h"
int main(int argc, char * argv[]){
    
    //=============================================================================
    // Step1: Check argument, open output\input file
    //=============================================================================
    FILE *in, *out;
    // Check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files for reading and writing 
    in = fopen(argv[1], "r");
    if( in==NULL ){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // ============================================================================= //
    // Step2: Read file input
    // ============================================================================= //
    int n, a, b;
    int num = fscanf(in, "%d %d %d\n\n", &n, &a, &b);
    if (num == EOF){
        fclose(in);
        fclose(out);
        return (0);
    }
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    for(int i = 0; i < a; i++){
        // +-------------------------------+ DEBUG USE +-------------------------------+ //
        // fprintf(stdout, "HELLO\n");
        // fflush(stdout);
        // +-------------------------------+ DEBUG END +-------------------------------+ //
        double data;
        int row, column;
        fscanf(in, "%d %d %lf\n", &row, &column, &data);
        // +-------------------------------+ DEBUG USE +-------------------------------+ //
        // fprintf(stdout, "%d %d %lf\n", row, column, data);
        // +-------------------------------+ DEBUG END +-------------------------------+ //
        changeEntry(A, row, column, data);
        
    }
    for(int i = 0; i < b; i++){
        double data;
        int row, column;
        fscanf(in, "%d %d %lf\n", &row, &column, &data);
        changeEntry(B, row, column, data);
    }

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);

    // ============================================================================= //
    // Step3: Perform matrix operation
    // ============================================================================= //
    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);

    Matrix D = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);

    Matrix E = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, E);

    Matrix F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);

    fprintf(out, "A-A =\n\n");

    Matrix G = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, G);

    Matrix H = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, H);

    Matrix I = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, I);

    //============================================================================== //
    // Step4: Close file and free momery alloc from heap
    //============================================================================== //
    // Close file pointer
    fclose(in);
    fclose(out);
    // Free memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);

    return 0;
}