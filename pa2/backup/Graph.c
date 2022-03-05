#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"Graph.h"

// private struct, not exported 
typedef struct GraphObj{
    // An array of Lists whose ith element contains the neighbors of vertex i.
    List* neighbors;    
    // An array of ints (or chars, or strings) whose ith element is the color 
    // (white, gray, black) of vertex i.
    List color;
    // An array of ints whose ith element is the parent of vertex i.         
    List parent;     
    // An array of ints whose ith element is the distance from the (most recent) 
    // source to vertex i.   
    List distance;   
    // The number of vertices.   
    int order;       
    // The number of edges.   
    int size;        
    // Label of the vertex that was most recently used as source for BFS.   
    int source;         
} GraphObj;


/*** Constructors-Destructors ***/ 
Graph newGraph(int n){
    Graph g = (Graph)malloc(sizeof(GraphObj));
    g->neighbors = (List*)calloc(n + 1, sizeof(List));
    for(int i = 0; i <= n; i++){
        g->neighbors[i] = newList();
    }
    g->color = newList();
    g->parent = newList();
    g->distance = newList();
    for(int i = 0; i <= n; i++){
        append(g->color, WHITE);
        append(g->distance, INF);
        append(g->parent, NIL);
    }
    g->order = n;
    g->size = 0;
    g->source = NIL;
    return g;
}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 0; i <= (*pG)->order; i++){
            freeList(&((*pG)->neighbors[i]));
        }
        freeList(&((*pG)->color));
        freeList(&((*pG)->parent));
        freeList(&((*pG)->distance));
        free((*pG)->neighbors);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G){
    return G->order;
}

int getSize(Graph G){
    return G->size;
}

int getSource(Graph G){
    return G->source;
}

int getParent(Graph G, int u){
    if(G->source == NIL){
        return NIL;
    }
    List parent = G->parent;
    moveFront(parent);
    while(index(parent) != u){
        moveNext(parent);
    }
    return get(parent);
}

int getDist(Graph G, int u){
    if(G->source == NIL){
        return INF;
    }
    List dist = G->distance;
    moveFront(dist);
    while(index(dist) != u){
        moveNext(dist);
    }
    return get(dist);
}

// Appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
// Precondition: 
//      1 ≤ 𝑢 ≤ getOrder(𝐺), getSource(G)!=NIL,
//      BFS() must be called before getPath().
void getPath(List L, Graph G, int u){
    // Fit with pa2-gunit-test.sh
    if(u == getSource(G)){
        append(L, u);
        return;
    }
    List newL = newList();
    append(newL, u);
    int p = getParent(G,u);
    append(newL, p);
    while(p != G->source && p != NIL){
        p = getParent(G, p);
        append(newL, p);
    }
    if(p == NIL && u != getSource(G)){
        append(L, NIL);
    }else{
        moveBack(newL);
        while (index(newL) >= 0)
        {
            append(L,get(newL));
            movePrev(newL);
        }
    }
    freeList(&newL);
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
    clear(G->color);
    clear(G->parent);
    clear(G->distance);
    for(int i = 0; i <= G->order; i ++){
        clear(G->neighbors[i]);
    }
    G->order = 0;
    G->source = NIL;
}


void addEdge(Graph G, int u, int v){
    if(u == v){
        return;
    }
    append(G->neighbors[u], v);
    append(G->neighbors[v], u);
    G->size += 1;
}

void addArc(Graph G, int u, int v){
    if(u == v){
        return;
    }
    append(G->neighbors[u], v);
    G->size += 1;
}

// Reference: Pseudo-code/GraphAlgorithms
void BFS(Graph G, int s){
    matainGraph(G);
    G->source = s;
    moveFront(G->color);
    moveFront(G->distance);
    moveFront(G->parent);
    for(int i = 0; i <= G->order; i++){
        set(G->color, WHITE);
        set(G->distance, INF);
        set(G->parent, NIL);
        moveNext(G->color);
        moveNext(G->distance);
        moveNext(G->parent);
    }
    moveFront(G->color);
    moveFront(G->distance);
    moveFront(G->parent);
    while (index(G->color) != s)
    {
        moveNext(G->color);
        moveNext(G->distance);
        moveNext(G->parent);
    }
    set(G->color, GRAY);
    set(G->distance, 0);
    set(G->parent, NIL);
    List queue = newList();
    append(queue, s);
    // Loop until queue is empty
    while(length(queue) > 0){
        int x = front(queue);
        deleteFront(queue);
        moveFront(G->neighbors[x]);
        // Iterate each adjecency of x
        while (index(G->neighbors[x]) >= 0){
            int y = get(G->neighbors[x]);
            // Get the distance from x to source
            moveFront(G->distance);
            while(index(G->distance) != x){
                moveNext(G->distance);
            }
            int x_dist = get(G->distance);
            // Move cursor to the proper index
            moveFront(G->color);
            moveFront(G->distance);
            moveFront(G->parent);
            while(index(G->color) != y){
                moveNext(G->color);
                moveNext(G->distance);
                moveNext(G->parent);
            }
            if(get(G->color) == WHITE){
                set(G->color, GRAY);
                set(G->distance, x_dist + 1);
                set(G->parent, x);
                append(queue, y);
            }
            moveNext(G->neighbors[x]);
        }
        moveFront(G->color);
        while (index(G->color) != x)
        {
            moveNext(G->color);
        }
        set(G->color, BLACK);
    }
    freeList(&queue);
}

/*** Other operations ***/
void debugGraph(FILE* out, Graph G){
    fprintf(out, "order: %d, size: %d, source: %d\n", G->order, G->size, G->source);
    moveFront(G->color);
    moveFront(G->parent);
    moveFront(G->distance);
    // Skip the first element
    moveNext(G->color);
    moveNext(G->parent);
    moveNext(G->distance);
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d's properties :\n", i);
        fprintf(out, "\t");
        fprintf(out ,"color: %d, parent: %d, distance: %d\n", get(G->color), get(G->parent), get(G->distance));
        moveNext(G->color);
        moveNext(G->parent);
        moveNext(G->distance);
    }
}

void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        moveFront(G->neighbors[i]);
        fprintf(out, "%d:", i);
        while(index(G->neighbors[i]) >= 0){
            int neighbor = get(G->neighbors[i]);
            fprintf(out, " %d", neighbor);
            moveNext(G->neighbors[i]);
        }
        fprintf(out, "\n");
    }
}

void matainGraph(Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        if(length(G->neighbors[i]) == 0){
            continue;
        }        
        // Perform insertion sort
        // Insert each data in G->neighbors[i] to L
        List L = newList();
        moveFront(G->neighbors[i]);
        append(L, get(G->neighbors[i]));
        moveNext(G->neighbors[i]);
        while(index(G->neighbors[i]) >= 0){
            moveFront(L);
            while(index(L) >= 0){
                if(get(L) > get(G->neighbors[i])){
                    break;
                }
                moveNext(L);
            }
            if(index(L) < 0){
                append(L, get(G->neighbors[i]));
            }else{
                insertBefore(L, get(G->neighbors[i]));
            }
            moveNext(G->neighbors[i]);
        }
        freeList(&(G->neighbors[i]));
        G->neighbors[i] = L;
    }
}
