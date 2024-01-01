/***
 * Author: Mignot Mesele
 * Title: FindComponents.c
 * Purpose: main implementation for finding strong connected components
 ***/


#include "Graph.h"


#define MAX_LEN 1000

int main(int argc, char* argv[]) {
    FILE* in, * out;
    char line[MAX_LEN];
    int num1, num2;
    char* token;
    Graph G;
    List S;
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
        addArc(G, num1, num2);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out,"\n");
    S = newList();
    for(int i = 1; i <= getOrder(G); i++){
    	append(S, i);
    }

    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);
    L =newList();
    int counter = 0;
    for(int j = 1; j <= getOrder(G); j++){
    	if(getParent(T, j) == NIL){
    		counter++;
    	}
    }
    
    int other_counter = counter - 1;
    moveBack(S);
    fprintf(out, "G contains %d strongly connected components:\n", counter);
    while(index(S) != -1){
    	prepend(L, get(S));
    	if(getParent(T, get(S)) == NIL){
    		fprintf(out, "Component %d: ",(counter - other_counter));
    		printList(out, L);
    		clear(L);
		other_counter--;
    	}
    	movePrev(S);
    }
 
    freeList(&S);
    freeList(&L);
    fclose(in);
    fclose(out);
    freeGraph(&G);

    return 0;
}

