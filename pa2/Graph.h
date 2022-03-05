// ---------------------------------------------------
// Header file for Graph ADT
// Help solve BFS problem
// ---------------------------------------------------
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include "List.h"

/*** Macros ***/
#define INF -1                          // Represent infinity vertex label.
#define NIL 0                           // Represent undefined vertex label.

#define WHITE 1                         // Undiscovered
#define GRAY 2                          // Discovering
#define BLACK 3                         // Finished


/*** Exported Type ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/ 

// Returns a Graph pointing to a newly created 
// GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n);                  

// Frees all heap memory associated with the Graph *pG
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG);              

/*** Access functions ***/

// Return the corresponding field values.
int getOrder(Graph G);                  

// Return the corresponding field values.

// Returns the source vertex most recently used in function.
int getSize(Graph G);                   

int getSource(Graph G);                 

// Will return the parent of vertex u in the Breadth-First tree 
// created by BFS(), or NIL if BFS() has not yet been called.
// Precondition: 
//      1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u);          
                                        
// Returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called
// Precondition: 
//      1 ≤ 𝑢 ≤ getOrder(𝐺)
//
int getDist(Graph G, int u);            

// Appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
// Precondition: 
//      1 ≤ 𝑢 ≤ getOrder(𝐺), getSource(G)!=NIL,
//      BFS() must be called before getPath().
// 
void getPath(List L, Graph G, int u);   
/*** Manipulation procedures ***/

// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);                

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

// Runs the BFS algorithm on the Graph G with source s, setting 
// the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);               
/*** Other operations ***/

// Prints the adjacency list representation of G to the file 
// pointed to by out.
void printGraph(FILE* out, Graph G);    

// For debug use.
void debugGraph(FILE* out, Graph G);    

// Maintain the adjacency lists in sorted order
void matainGraph(Graph G);
#endif