#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"Graph.h"

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

    //=============================================================================
    // Step2: Read the first part of input file
    //=============================================================================
    int n = 0;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);
    Graph T = NULL;
    List S = newList();
    for(int i=1; i<=n; i++) append(S, i);

    int vertexU,vertexV;
    fscanf(in, "%d %d\n", &vertexU, &vertexV);
    while(vertexU != 0 || vertexV != 0){
        addArc(G, vertexU, vertexV);
        fscanf(in, "%d %d\n", &vertexU, &vertexV);
    }

    // Your Graph ADT should maintain the adjacency lists in sorted order
    matainGraph(G);

    // After these lines are read your program will print the 
    // adjacency list representation of the graph to the output file.
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    //=============================================================================
    // Step3: Find components
    //=============================================================================
    T = transpose(G);
    DFS(G, S);
    DFS(T, S);  // S is sorted by decreasing finish times.
    
    List R = newList(); // Store the roots of every strong connection components.
    int count = 0;
    moveFront(S);
    while(index(S) >= 0){
        // If ith vertices in S have no parent (parent[i] == NULL),  then i is a strong
        // connection components root
        if(getParent(T, get(S)) == NIL){
            count++;
            prepend(R, get(S)); // Store root in topological sort
        }
        moveNext(S);
    }
    fprintf(out, "\nG contains %d strongly connected components:\n", count);
    
    int k = 1;
    moveFront(R);
    while(index(R) >= 0){
        fprintf(out, "Component %d: ", k++);
        List components = newList();

        if(index(S) < 0) moveBack(S);
        while(index(S) >= 0){
            // +-------------------------------+ DEBUG USE +-------------------------------+ //
            // fprintf(stderr, "DEBUG: get(R) = %d, get(S) = %d\n", get(R), get(S));
            // +-------------------------------+ DEBUG END +-------------------------------+ //
            if(getParent(T,get(S)) == NIL){
                // fprintf(out, " %d", get(S));
                prepend(components, get(S));
                movePrev(S);
                break;
            }
            prepend(components, get(S));
            // fprintf(out, " %d", get(S));
            movePrev(S);
        }
        printList(out, components);
        fprintf(out, "\n");
        freeList(&components);
        moveNext(R);
    }

    //=============================================================================
    // Step4: Close file and free momery alloc from heap
    //=============================================================================
    // Close file pointer
    fclose(in);
    fclose(out);
    // Free Graph
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    freeList(&R);
    return(0);
}