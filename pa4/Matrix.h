#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_

#include<stdio.h>

typedef struct MatrixObj* Matrix;

// Returns a reference to a new n*n Matrix object in the zero state.
Matrix newMatrix(int n);

void freeMatrix(Matrix* pM);

int size(Matrix M);

int NNZ(Matrix M);

// Return true (1) if matrices A and B are equal, false (0) otherwise. 
int equals(Matrix A, Matrix B);

// Re-sets M to the zero Matrix state
void makeZero(Matrix M);

// Changes the ith row, jth column of M to the value x. 
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);

Matrix copy(Matrix A);

Matrix transpose(Matrix A);

Matrix scalarMult(double x, Matrix A);

Matrix sum(Matrix A, Matrix B);

// Returns a reference to a new Matrix object A-B
Matrix diff(Matrix A, Matrix B);

Matrix product(Matrix A, Matrix B);

void printMatrix(FILE* out, Matrix M);

#endif
