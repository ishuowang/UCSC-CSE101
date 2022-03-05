#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"Graph.h"

void moveCursor(List L, int i);
// TODO: this is helper function, should be move in List.c
// Move the cursor in the List to index ith position
// Precondition:
//      0 <= i <= length(L);
void moveCursor(List L, int i){
    while(index(L) != i){
        if(index(L) == -1) moveFront(L);
        if(index(L) < i) moveNext(L);
        if(index(L) > i) movePrev(L);
    }
}

void visit(Graph G, int x, int *timePtr);

// private struct, not exported 
typedef struct GraphObj{
    // An array of Lists whose ith element contains the neighbors of vertex i.
    List* neighbors;    
    // An array of ints (or chars, or strings) whose ith element is the color 
    // (white, gray, black) of vertex i.
    List color;
    // An array of ints whose ith element is the parent of vertex i.         
    List parent;
    // An array of ints whose ith element is the discover time of vertex i.
    List discover;
    // An array of ints whose ith element is the finish time of vertex i.
    List finish;
    // The number of vertices.   
    int order;
    // The number of edges.   
    int size;
} GraphObj;

Graph newGraph(int n){
    Graph g = (Graph)malloc(sizeof(GraphObj));
    g->neighbors = (List*)calloc(n + 1, sizeof(List));
    for(int i = 0; i <= n; i++){
        g->neighbors[i] = newList();
    }
    g->color = newList();
    g->parent = newList();
    g->discover = newList();
    g->finish = newList();
    for(int i = 0; i <= n; i++){
        append(g->color, WHITE);
        append(g->parent, NIL);
        append(g->discover, UNDEF);
        append(g->finish, UNDEF);
    }
    g->order = n;
    g->size = 0;
    return g;
}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 0; i <= (*pG)->order; i++){
            freeList(&((*pG)->neighbors[i]));
        }
        freeList(&((*pG)->color));
        freeList(&((*pG)->parent));
        freeList(&((*pG)->discover));
        freeList(&((*pG)->finish));
        free((*pG)->neighbors);
        free(*pG);
        *pG = NULL;
    }
}

int getOrder(Graph G){
    return G->order;
}

int getSize(Graph G){
    return G->size;
}

int getParent(Graph G, int u){
    moveCursor(G->parent, u);
    return get(G->parent);
}

int getDiscover(Graph G, int u){
    moveCursor(G->discover, u);
    return get(G->discover);
}

int getFinish(Graph G, int u){
    moveCursor(G->finish, u);
    return get(G->finish);
}

void addEdge(Graph G, int u, int v){
    append(G->neighbors[u], v);
    append(G->neighbors[v], u);
    G->size += 1;
    matainGraph(G);
}

void addArc(Graph G, int u, int v){
    append(G->neighbors[u], v);
    G->size += 1;
    matainGraph(G);
}

// TODO: After DFS, List S should store vertices
// sorted by decreasing finish times
void DFS(Graph G, List S){
    moveFront(S);
    while(index(S) >= 0){
        int x = get(S);
        moveCursor(G->color, x);
        set(G->color, WHITE);
        moveCursor(G->parent, x);
        set(G->parent, NIL);
        moveNext(S);
    }
    int time = 0;
    moveFront(S);
    while (index(S) >= 0){
        int x = get(S);
        moveCursor(G->color, x);
        int color = get(G->color);  // color is the value of color[x]
        if(color == WHITE){
            // x is the root of strong components
            visit(G, x, &time);
        }
        moveNext(S);
    }

    // Sort S by decreasing finish times
    List L = newList();
    append(L, 1);
    moveFront(L);
    for(int i = 2; i <= length(S); i++){ // insert the ith element
        moveFront(L);
        while(index(L) >= 0){
            if(getFinish(G, i) < getFinish(G, get(L))){
                break;
            }
            moveNext(L);
        }
        if(index(L) < 0){
            append(L, i);
        }else{
            insertBefore(L,i);
        }
    }

    moveFront(S);
    moveBack(L);
    while (index(S) >= 0)
    {
        set(S, get(L));
        moveNext(S);
        movePrev(L);
    }
    freeList(&L);
}

void visit(Graph G, int x, int *timePtr){
    moveCursor(G->discover, x);
    *timePtr += 1;
    set(G->discover, *timePtr);
    moveCursor(G->color, x);
    set(G->color, GRAY);
    
    moveFront(G->neighbors[x]);
    while(index(G->neighbors[x]) >= 0){
       int  y = get(G->neighbors[x]);
       moveCursor(G->color, y);
       int color = get(G->color);
       if (color == WHITE){
           moveCursor(G->parent, y);
           set(G->parent, x);           //p[y] = x
           visit(G, y, timePtr);
       }
        moveNext(G->neighbors[x]);
    }
    moveCursor(G->color, x);
    set(G->color, BLACK);
    moveCursor(G->finish, x);
    *timePtr += 1;
    set(G->finish, *timePtr);
}


Graph transpose(Graph G){
    Graph G_t = newGraph(getOrder(G));  // Transpoesed G
    for(int i = 0; i <= getOrder(G); i++){
        moveFront(G->neighbors[i]);
        while(index(G->neighbors[i]) >= 0){
            int neighbor = get(G->neighbors[i]);
            addArc(G_t, neighbor, i);
            moveNext(G->neighbors[i]);
        }
    }
    return G_t;
}

Graph copyGraph(Graph G){
    Graph newG = (Graph)malloc(sizeof(GraphObj));
    newG->neighbors = (List*)calloc(getOrder(G) + 1, sizeof(List));
    for(int i = 0; i <= getOrder(G); i++){
        newG->neighbors[i] = newList();
    }
    for(int i = 0; i <= getOrder(G); i++){
        moveFront(G->neighbors[i]);
        while(index(G->neighbors[i]) >= 0){
            int neighbor = get(G->neighbors[i]);
            addArc(newG, i, neighbor);
            moveNext(G->neighbors[i]);
        }
    }
    newG->color = copyList(G->color);
    newG->parent = copyList(G->parent);
    newG->discover = copyList(G->discover);
    newG->finish = copyList(G->finish);
    // newG->size is setted while performming addArc()
    newG->order = getOrder(G);
    return newG;
}

void debugGraph(FILE* out, Graph G){
    fprintf(out, "order: %d, size: %d\n", G->order, G->size);
    moveFront(G->color);
    moveFront(G->parent);
    moveFront(G->discover);
    moveFront(G->finish);
    // Skip the first element
    moveNext(G->color);
    moveNext(G->parent);
    moveNext(G->discover);
    moveNext(G->finish);
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d's properties :\n", i);
        fprintf(out, "\t");
        fprintf(out ,"color: %d, parent: %d, discover: %d finish:%d\n, ", get(G->color), get(G->parent), get(G->discover), get(G->finish));
        moveNext(G->color);
        moveNext(G->parent);
        moveNext(G->discover);
        moveNext(G->finish);
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
