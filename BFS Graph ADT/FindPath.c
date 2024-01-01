/***
 * Author: Mignot Mesele
 * Title: FindPath.c
 * Purpose: main implementation for finding shortest path
 ***/


#include "Graph.h"


#define MAX_LEN 1000

int main(int argc, char* argv[]) {
    FILE* in, * out;
    char line[MAX_LEN];
    int num1, num2;
    char* token;
    Graph G;
    List L;

    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    if(fgets(line, MAX_LEN, in) != NULL){
        G = newGraph(atoi(line));
    }       


    while (fgets(line, MAX_LEN, in) != NULL) {
        token = strtok(line, " ");
        if (token != NULL) {
            num1 = atoi(token);
            token = strtok(NULL, " ");
        }
        if (token != NULL) {
            num2 = atoi(token);
        }

        if (num1 == 0 && num2 == 0) {
            break;
        }
        addEdge(G, num1, num2);
    }

    printGraph(out, G);

    while (fgets(line, MAX_LEN, in) != NULL) {
        token = strtok(line, " ");
        if (token != NULL) {
            num1 = atoi(token);
            token = strtok(NULL, " ");
        }
        if (token != NULL) {
            num2 = atoi(token);
        }

        if (num1 == 0 && num2 == 0) {
            break;
        }

        BFS(G, num1);
	if(getDist(G, num2) == -1){
		fprintf(out, "The distance from %d to %d is infinity\n", num1, num2);
	}else{
        	fprintf(out, "The distance from %d to %d is %d\n", num1, num2, getDist(G, num2));
	}
        L = newList();
        getPath(L, G, num2);

        if (getDist(G, num2) == -1) {
            fprintf(out, "No %d-%d path exists\n", num1, num2);
        } else {
            fprintf(out, "A shortest %d-%d path is: ", num1, num2);
            printList(out, L);
        }

        freeList(&L);
    }

    fclose(in);
    fclose(out);
    freeGraph(&G);

    return 0;
}
