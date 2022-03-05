#include"Graph.h"

void printError(){
    printf("Error behaviour\n");
}

int main(int argc, char const *argv[]){   
    Graph G = newGraph(10);
    if(getOrder(G) != 10){
        printError();
        return -1;
    }
    if(getSize(G) != 0){
        printError();
        return -1;
    }
    if(getSource != NIL){
        printError();
        return -1;
    }
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addArc(G,4,5);
    BFS(G, 1);
    if(getDist(G,4) != 2){
        printError();
        return -1;
    }
    List expectPath = newList();
    append(expectPath,1);
    append(expectPath,2);
    append(expectPath,3);
    List outPath = newList();
    getPath(outPath, G, 4);
    if(! equals(expectPath, outPath)){
        printError();
        return -1;
    }
    freeGraph(G);
    return 0;
}

