#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include"Graph.h"

int main(int argc, char * argv[]){
    //=============================================================================
    // Step1: Check argument, open output\input file
    //=============================================================================
    FILE *in, *out;
    // check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
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
    int n;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    int vertexU,vertexV;
    fscanf(in, "%d %d\n", &vertexU, &vertexV);
    while(vertexU != 0 || vertexV != 0){
        addEdge(G, vertexU, vertexV);
        fscanf(in, "%d %d\n", &vertexU, &vertexV);
    }

    // Your Graph ADT should maintain the adjacency lists in sorted order
    matainGraph(G);


    // After these lines are read your program will print the 
    // adjacency list representation of the graph to the output file.
    printGraph(out, G);

    //=============================================================================
    // Step3: Read the second part of input file
    //=============================================================================
    int source,destination;
    fscanf(in, "%d %d\n", &source, &destination);

    while(source != 0 || destination != 0){
        // if source equal to dest, then there always a path which dist is 0.
        if(source == destination){
            fprintf(out, "\nThe distance from %d to %d is 0\n", source, destination);
            fprintf(out, "A shortest %d-%d path is: %d\n", source, destination, source);
            fscanf(in, "%d %d\n", &source, &destination);
            continue;
        }
        // Perform a Breadth First Search (BFS) from the given source vertex.
        BFS(G, source);
        // Print out the distance from the source  to the destination
        int dist = getDist(G, destination);
        if(dist == -1){
            fprintf(out, "\nThe distance from %d to %d is infinity\n", source, destination);
        }else{
            fprintf(out, "\nThe distance from %d to %d is %d\n", source, destination, dist);
        }
        // Use the parent pointers to print out a shortest path
        List path = newList();
        getPath(path, G, destination);
        if(front(path) == NIL){
            fprintf(out, "No %d-%d path exists\n", source, destination);
        }else{
            fprintf(out, "A shortest %d-%d path is: ", source, destination);
            printList(out, path);
        }
        freeList(&path);
        fscanf(in, "%d %d\n", &source, &destination);
    }

    // Close files
    fclose(in);
    fclose(out);
    // Free Graph
    freeGraph(&G);
    return(0);
}