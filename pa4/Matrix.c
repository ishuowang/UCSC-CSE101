#include "List.h"
#include "Matrix.h"
#include "stdlib.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    double data;
    int index;
} EntryObj;

// Create a entry of data d, and index i.
Entry newEntry(double d, int i){
    Entry E = malloc(sizeof(EntryObj));
    E->data = d;
    E->index = i;
    return E;
}

void freeEntry(Entry* pE){
    if(pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
        pE = NULL;
    }
}

typedef struct MatrixObj{
    // Rows in matrix, each row is a List ADT which contains sevral entrys.
    List* rows;
    // The size of square Matrix
    int size;
    // The Number of None Zero element
    int nnz;        
}MatrixObj;

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    M->rows = calloc(n + 1, sizeof(List));
    for(int i = 0; i <= n; i++){
        M->rows[i] = newList();
        // for(int j = 0; j <= n; j++){
        //     Entry E = newEntry(0, j);
        //     append(M->rows[i], E);
        // }
    }
    M->size = n;
    M->nnz = 0;
    return M;
}

// Move the cursor in the List to index ith position
// Precondition:
//      0 <= i <= length(L);
//      List L contains Entry which index = i;
void moveCursor(List L, int i){
    while(((Entry)get(L))->index != i){
        if(index(L) == -1) moveFront(L);
        if(((Entry)get(L))->index < i) moveNext(L);
        if(((Entry)get(L))->index > i) movePrev(L);
    }
}
Entry getEntry(Matrix M ,int i, int j){
    List row = M->rows[i];
    for(moveFront(row); index(row) >= 0; moveNext(row)){
        Entry E = get(row);
        if(E->index == j){
            return E;
        }
    }
    return NULL;
}

void freeMatrix(Matrix* pM){
    if(pM != NULL && *pM != NULL){
        for(int i = 0; i <= size(*pM); i++){
            List row = (*pM)->rows[i];
            for(moveFront(row); index(row) >= 0; moveNext(row)){
                Entry E = get(row);
                freeEntry(&E);
            }
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free((*pM));
        *pM = NULL;
        pM = NULL;
    }
}

int size(Matrix M){
    return M->size;
}

int NNZ(Matrix M){
    return M->nnz;
}

bool equalsEntry(Entry A, Entry B){
    return A->data == B->data && A->index == B->index;
}

bool equalsRow(List A, List B){
    for(moveFront(A), moveFront(B); index(A) >=0 && index(B) >= 0; moveNext(A), moveNext(B)){
        Entry a = get(A);
        Entry b = get(B);
        if(!equalsEntry(a, b)){
            return false;
        }
    }
    return true;
}

int equals(Matrix A, Matrix B){
    if(A->size != B->size || A->nnz != B->nnz){
        return 0;
    }
    for(int i = 0; i <= size(A); i++){
        if(!equalsRow(A->rows[i], A->rows[i])){
            return 0;
        }
    }
    return 1;
}

void makeZero(Matrix M){
    for(int i = 0; i < size(M); i++){
        List row = M->rows[i];
        while(length(row) > 0){
            deleteFront(row);
        }
    }
    M->nnz = 0;
}

// If M doesn't have ith row, jth column Entry, create a new Entry and insert it into the proper position
// If M have ith row, jth column Entry, then change the value of such Entry.
void changeEntry(Matrix M, int i, int j, double x){
    Entry E = getEntry(M, i, j);
    if(E == NULL){  // M_ij doesn't exist.
        if(x == 0){
            return;
        }
        List row = M->rows[i];
        // move cursor of ith row to a proper position for inserting a new Entry.
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            if(((Entry)get(row))->index > j){
                break;
            }
        }
        // append a new Entry to a proper position in ith row.
        if(index(row) >= 0){
            insertBefore(row, newEntry(x, j));
        }else{
            append(M->rows[i], newEntry(x, j));
        }
        // Change NNZ field
        M->nnz ++;
    }else{  // M_ij exist.
        // Change NNZ field
        if(x == 0){
            moveCursor(M->rows[i], j);
            freeEntry(&E);
            delete(M->rows[i]);
            M->nnz -= 1;
            return;
        }
        E->data = x;
    }
}

Matrix copy(Matrix A){
    Matrix copyA = newMatrix(size(A));
    copyA->nnz = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->rows[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry E = get(row);
            append(copyA->rows[i], newEntry(E->data, E->index));
        }
    }
    return copyA;
}

Matrix transpose(Matrix A){
    Matrix T = newMatrix(size(A));
    T->nnz = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->rows[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry E = get(row);
            append(T->rows[E->index], newEntry(E->data, i));
        }
    }
    return T;
}

Matrix scalarMult(double x, Matrix A){
    Matrix scalarA = newMatrix(size(A));
    scalarA->nnz = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->rows[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry E = get(row);
            append(scalarA->rows[i], newEntry(x * E->data, E->index));
            if(x == 0){
                scalarA->nnz -= 1;
            }
        }
    }
    return scalarA;
}

Matrix sum(Matrix A, Matrix B){
    B = copy(B);
    Matrix sumAB = newMatrix(size(A));
    for(int i = 0; i <= size(A); i++){
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        for(moveFront(rowA), moveFront(rowB); index(rowA) >= 0 && index(rowB) >= 0; ){
            Entry E_A = get(rowA);
            Entry E_B = get(rowB);
            if(E_A->index == E_B->index){
                append(sumAB->rows[i], newEntry(E_A->data + E_B->data, E_A->index));
                if(E_A->data + E_B->data == 0){
                    deleteBack(sumAB->rows[i]);
                    sumAB->nnz -= 1;
                }
                moveNext(rowA);
                moveNext(rowB);
            }else if (E_A->index < E_B->index){
                append(sumAB->rows[i], newEntry(E_A->data, E_A->index));
                moveNext(rowA);
            }else if (E_A->index > E_B->index){
                append(sumAB->rows[i], newEntry(E_B->data, E_B->index));
                moveNext(rowB);
            }
            sumAB->nnz += 1;
        }
        while (index(rowA) >= 0){
            Entry E_A = get(rowA);
            append(sumAB->rows[i], newEntry(E_A->data, E_A->index));
            sumAB->nnz += 1;
            moveNext(rowA);
        }
        while (index(rowB) >= 0){
            Entry E_B = get(rowB);
            append(sumAB->rows[i], newEntry(E_B->data, E_B->index));
            sumAB->nnz += 1;
            moveNext(rowB);
        }
    }
    freeMatrix(&B);
    return sumAB;
}

Matrix diff(Matrix A, Matrix B){
    B = copy(B);
    Matrix diffAB = newMatrix(size(A));
    for(int i = 0; i <= size(A); i++){
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        for(moveFront(rowA), moveFront(rowB); index(rowA) >= 0 && index(rowB) >= 0; ){
            Entry E_A = get(rowA);
            Entry E_B = get(rowB);
            if(E_A->index == E_B->index){
                append(diffAB->rows[i], newEntry(E_A->data - E_B->data, E_A->index));
                if(E_A->data - E_B->data == 0){
                    diffAB->nnz -= 1;
                }
                moveNext(rowA);
                moveNext(rowB);
            }else if (E_A->index < E_B->index){
                append(diffAB->rows[i], newEntry(E_A->data, E_A->index));
                moveNext(rowA);
            }else if (E_A->index > E_B->index){
                append(diffAB->rows[i], newEntry(0 - E_B->data, E_B->index));
                moveNext(rowB);
            }
            diffAB->nnz += 1;
        }
        // Append the rest Entry in rowA or rowB
        while (index(rowA) >= 0){
            Entry E_A = get(rowA);
            append(diffAB->rows[i], newEntry(E_A->data, E_A->index));
            diffAB->nnz += 1;
            moveNext(rowA);
        }
        while (index(rowB) >= 0){
            Entry E_B = get(rowB);
            append(diffAB->rows[i], newEntry(0 - E_B->data, E_B->index));
            diffAB->nnz += 1;
            moveNext(rowB);
        }
    }
    freeMatrix(&B);
    return diffAB;
}

// Helper function
double vectorDot(List P, List Q){
    double result = 0.0;
    for(moveFront(P), moveFront(Q); index(P) >= 0 && index(Q) >= 0; ){
        Entry p = get(P);
        Entry q = get(Q);
        if(p->index == q->index){
            result += p->data * q->data;
            moveNext(P);
            moveNext(Q);
        }else if (p->index < q->index){
            moveNext(P);
        }else if(p->index > q->index){
            moveNext(Q);
        }
    }
    return result;
}

Matrix product(Matrix A, Matrix B){
    Matrix newB = transpose(B);
    Matrix productAB = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++){
        for(int j = 1; j <= size(A); j++){
            // moveCursor(A->rows[i], j);
            // moveCursor(B->rows[i], j);
            // Entry aEntry = get(A->rows[i]);
            // Entry bEntry = get(B->rows[i]);
            double product = vectorDot(A->rows[i], newB->rows[j]);
            if(product != 0.0){
                append(productAB->rows[i], newEntry(product, j));
                productAB->nnz += 1;
            }
        }
    }
    freeMatrix(&newB);
    return productAB;
}

// Helper function for printMatrix
void cat(FILE* out, List L){
    moveFront(L);
    while(index(L) >= 0){
        Entry E = get(L);
        if(E->data != 0) fprintf(out, "(%d, %.1lf) ", E->index, E->data);
        moveNext(L);
    }
}

void printMatrix(FILE* out, Matrix M){
    for(int i = 0; i <= size(M); i++){
        moveFront(M->rows[i]);
        while(index(M->rows[i]) >= 0){
            if(((Entry)get(M->rows[i]))->data != 0.0){
                fprintf(out, "%d: ", i);
                cat(out, M->rows[i]);
                fprintf(out, "\n");
                break;
            }
            moveNext(M->rows[i]);
        }
    }
    fprintf(out, "\n");
}
