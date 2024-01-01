/***
 * Author: Mignot Mesele
 * Title: GraphTest.c
 * Purpose: Testing script for Graph ADT
 * ***/

#include "Graph.h"

int main() {
    Graph G;
    int n = 5;

    G = newGraph(n);
    printf("Test 1: Create a new graph\n");
    printGraph(stdout, G);

    printf("\nTest 2: Add arcs to the graph\n");
    addArc(G, 1, 2);
    addArc(G, 1, 3);
    addArc(G, 2, 4);
    addArc(G, 3, 5);
    printGraph(stdout, G);

    printf("\nTest 3: Adding duplicates (should not add duplicates)\n");
    addArc(G, 1, 2);
    addArc(G, 2, 4);
    printGraph(stdout, G);

    printf("\nTest 4: Get graph properties\n");
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));

    printf("\nTest 5: Get Parent, Discover, and Finish times\n");
    for (int i = 1; i <= n; i++) {
        printf("Parent of %d: %d\n", i, getParent(G, i));
        printf("Discover time of %d: %d\n", i, getDiscover(G, i));
        printf("Finish time of %d: %d\n", i, getFinish(G, i));
    }

    printf("\nTest 6: Add Edge\n");
    addEdge(G, 1, 4);
    printGraph(stdout, G);

    printf("\nTest 7: Perform a depth-first search (DFS)\n");
    List S = newList();
    for(int j =1; j <= getOrder(G); j++){
    	append(S, j);
    }
    printf("newlist made\n");
    DFS(G, S);
    printf("DFS result: ");
    printList(stdout, S);
    freeList(&S);

    printf("\nTest 8: Create a transposed graph\n");
    Graph T = transpose(G);
    printGraph(stdout, T);

    printf("\nTest 9: Create a copy of the original graph\n");
    Graph CG = copyGraph(G);
    printGraph(stdout, CG);

    printf("\nTest 10: Free the graphs\n");
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&CG);

    return 0;
}
