#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include "List.h"

#define UNDEF -1      // Represent undefined time.
#define NIL 0         // Represent vertex have no parent.

#define WHITE 1       // Undiscovered
#define GRAY 2        // Discovering
#define BLACK 3       // Finished


typedef struct GraphObj* Graph;


// Returns a Graph pointing to a newly created 
// GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n);                  

// Frees all heap memory associated with the Graph *pG
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG);              


// Returns the number of vertices in G.
int getOrder(Graph G);                  

// Returns the number of edges in G.
int getSize(Graph G);                               

// Will return the parent of vertex u in the Breadth-First tree 
// created by BFS(), or NIL if BFS() has not yet been called.
// Precondition: 
//      1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u);          
                                        
// Returns the discover time of vertex u,
// or UNDEF if DFS() has not yet been called
// Precondition: 
//      1 ≤ 𝑢 ≤ getOrder(𝐺)
//
int getDiscover(Graph G, int u);            

// Returns the finished time of vertex u,
// or UNDEF if DFS() has not yet been called
// Precondition: 
//      1 ≤ 𝑢 ≤ getOrder(𝐺)
//
int getFinish(Graph G, int u);

// Inserts a new edge joining u to v, i.e. u is added to the adjacency 
// List of v, and v to the adjacency List of u.
// Precondition:  
//      1 <= u,v <= getOrder(G).
// 
void addEdge(Graph G, int u, int v); 

// Inserts a new directed edge from u to v, i.e. v is added to the
// adjacency List of u (but not u to the adjacency List of v)
// Precondition:  
//      1 <= u,v <= getOrder(G).
//
void addArc(Graph G, int u, int v);     

// Function DFS() will perform the depth first search algorithm on 𝐺. 
// The List argument 𝑆 has two purposes in this function. First it 
// defines the order in which vertices are to be processed in the main 
// loop (5-7) of DFS. Second, when DFS is complete, it will store the 
// vertices by decreasing finish times (hence 𝑆 is considered to be a 
// stack). Thus 𝑆 can be classified as both an input and output parameter 
// to function DFS().
// Perconditions:
//      length(𝑆) == 𝑛, S contains some permutation of the 
//      integers {1, 2, ... , 𝑛} where 𝑛 = getOrder(𝐺).
void DFS(Graph G, List S);               

// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

// Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);

// Prints the adjacency list representation of G to the file 
// pointed to by out.
void printGraph(FILE* out, Graph G);    

// For debug use.
void debugGraph(FILE* out, Graph G);    

// Maintain the adjacency lists in sorted order
void matainGraph(Graph G);
#endif