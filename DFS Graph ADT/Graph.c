/***
 * Author: Mignot Mesele
 * Title: Graph.c
 * Purpose: Graph ADT
 ***/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

/*** structs ***/

typedef struct GraphObj{
	List *adj;
	int *color;
	int *parent;
	int *discover;
	int *finish;
	int order;
	int size;
}GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n){
	Graph G = (Graph)malloc(sizeof(GraphObj));
	G->adj = malloc((n+1) * sizeof(List));
	G->order = n;
	G->size = 0;
	G->color = (int*)malloc((n+1) * sizeof(int));
	G->parent = (int*)malloc((n+1) * sizeof(int));
	G->discover = (int*)malloc((n+1) * sizeof(int));
	G->finish = (int*)malloc((n+1) * sizeof(int));
	for( int i = 1; i <= n; i++){
		G->adj[i] = newList();
		G->color[i] = 0;
                G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
                G->parent[i] = NIL;
	}
	return G;
}

void freeGraph(Graph* pG){
	if(pG != NULL && *pG != NULL){
		makeNull(*pG);
		for(int i = 1; i <= getOrder(*pG); i++){
			freeList(&((*pG)->adj[i]));
		}
		free((*pG)->adj);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->discover);
		free((*pG)->finish);
		free(*pG);
		(*pG) = NULL;
	}
}

/*** Access functions ***/
	
int getOrder(Graph G){
	return G->order;
}

int getSize(Graph G){
	return G->size;
}	


int getParent(Graph G, int u){
	if(G == NULL){
		exit(EXIT_FAILURE);
	}
	if(u >= 1 && u <= getOrder(G)){
		return G->parent[u];
	}else{
		exit(EXIT_FAILURE);
	}
}

int getDiscover(Graph G, int u){
	 if(G == NULL){
                exit(EXIT_FAILURE);
        }
        if(u >= 1 && u <= getOrder(G)){
                return G->discover[u];
        }else{
                exit(EXIT_FAILURE);
        }
}

int getFinish(Graph G, int u){
         if(G == NULL){
                exit(EXIT_FAILURE);
        }
        if(u >= 1 && u <= getOrder(G)){
                return G->finish[u];
        }else{
                exit(EXIT_FAILURE);
        }
}
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		exit(EXIT_FAILURE);
	}
	if(u >= 1 && v >= 1 && u <= getOrder(G) && v <= getOrder(G)){
		addArc(G, u, v);
		addArc(G, v, u);
		G->size--;
	}else{
		exit(EXIT_FAILURE);
	}
}

void addArc(Graph G, int u, int v){
        if(G == NULL){
                exit(EXIT_FAILURE);
        }
        if(u >= 1 && v >= 1 && u <= getOrder(G) && v <= getOrder(G)){
		if( list_is_empty(G->adj[u])){
			prepend(G->adj[u], v);
			G->size++;
			return;
		}else{
                	moveFront(G->adj[u]); 
			while (index(G->adj[u]) != -1 && v > get(G->adj[u])) { 
				moveNext(G->adj[u]);
            		}
            		if (index(G->adj[u]) == -1) {
                		append(G->adj[u], v);
            		} else {
				if(v == get(G->adj[u])){
                                	return;
                        	}else{
			
                			insertBefore(G->adj[u], v);
				}
            		}
        	}
        	G->size++;
    	} else {
        	exit(EXIT_FAILURE);
    	}
}
void makeNull(Graph G){
	for(int i = 1; i <= getOrder(G); i++){
		clear(G->adj[i]);
	}
}

/* 0 = white 1 = grey 2 = black*/
void DFS(Graph G, List S){
	if(G == NULL || S == NULL){
		exit(EXIT_FAILURE);
	}
	if(length(S) != getOrder(G)){
		exit(EXIT_FAILURE);
	}
	List L = copyList(S);
	clear(S);
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = 0;
		G->parent[i] = NIL;
	}
	moveFront(L);
	int time = 0;
	for( int j = 1; j <= getOrder(G); j++){
		if(G->color[get(L)] == 0){
			Visit(G, S, get(L), &time);
		}
		moveNext(L);
	}
	freeList(&L);
}

void Visit(Graph G, List s, int x, int* time){
	G->discover[x] = ++(*time);
	G->color[x]=1;
	moveFront(G->adj[x]);
	for(int i = 0; i < length(G->adj[x]); i++){
		if(G->color[get(G->adj[x])] == 0){
			G->parent[get(G->adj[x])] = x;
			Visit(G, s, get(G->adj[x]), time);
		}
		moveNext(G->adj[x]);
	}
	G->color[x] = 2;
	G->finish[x] = (++(*time));
	prepend(s, x);
	
}
/*** other operations ***/
Graph transpose(Graph G){
	Graph T = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		if(!(list_is_empty(G->adj[i]))){
			
			moveFront(G->adj[i]);
			for (int j =0 ; j < length(G->adj[i]); j++){	
				addArc(T,get(G->adj[i]),i);
				moveNext(G->adj[i]);
			}
		}
	}
	return T;
}
  


Graph copyGraph(Graph G){
	Graph CG = newGraph(getOrder(G));
	CG->order = getOrder(G);
	CG->size = getSize(G);
	for( int i = 1; i <= getOrder(G); i++){
                //CG->adj[i] = G->adj[i];
		if(!(list_is_empty(G->adj[i]))){

                        moveFront(G->adj[i]);
                        for (int j =0 ; j < length(G->adj[i]); j++){
                                addArc(CG,i, get(G->adj[i]));
                                moveNext(G->adj[i]);
                        }
                }

		CG->color[i] = G->color[i];
        	CG->discover[i] = G->discover[i];
        	CG->finish[i] = G->finish[i];
        	CG->parent[i] = G->parent[i];
	}
	return CG;
}

void printGraph(FILE* out, Graph G){
	for( int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
	}
}

