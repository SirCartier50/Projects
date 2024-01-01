/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{2}
 * GraphTest.c
 * tests Graph ADT
 * ***/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main() {
    Graph G;
    int numVertices = 6;

    G = newGraph(numVertices);

    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 6);

    printf("Adjacency List of the Graph:\n");
    printGraph(stdout, G);
    printf("\n");

    printf("Graph Order (Number of Vertices): %d\n", getOrder(G));
    printf("Graph Size (Number of Edges): %d\n", getSize(G));
    printf("Source Vertex: %d\n", getSource(G));

    printf("\nBreadth-First Search from Vertex 1:\n");
    BFS(G, 1);

    printf("Parent: ");
    for (int i = 1; i <= numVertices; i++) {
        printf("%d ", getParent(G, i));
    }
    printf("\n");

    printf("Distance: ");
    for (int i = 1; i <= numVertices; i++) {
        printf("%d ", getDist(G, i));
    }
    printf("\n");

    List path = newList();
    int targetVertex = 6;

    getPath(path, G, targetVertex);

    printf("Path from 1 to %d: ", targetVertex);
    printList(stdout, path);
    printf("\n");

    freeGraph(&G);
    freeList(&path);

    return 0;
}

