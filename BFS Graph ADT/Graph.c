/***
 * Author: Mignot Mesele
 * Title: Graph.c
 * Purpose: Graph ADT
 * ***/

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
	int *distance;
	int order;
	int size;
	int source;
}GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n){
	Graph G = (Graph)malloc(sizeof(GraphObj));
	G->adj = malloc((n+1) * sizeof(List));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	G->color = (int*)malloc((n+1) * sizeof(int));
	G->parent = (int*)malloc((n+1) * sizeof(int));
	G->distance = (int*)malloc((n+1) * sizeof(int));
	for( int i = 1; i <= n; i++){
		G->adj[i] = newList();
		G->color[i] = 0;
                G->distance[i] = INF;
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
		free((*pG)->distance);
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
//check this for errors with source vertex
int getSource(Graph G){
	return G->source;
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

int getDist(Graph G, int u){
	 if(G == NULL){
                exit(EXIT_FAILURE);
        }
        if(u >= 1 && u <= getOrder(G)){
                return G->distance[u];
        }else{
                exit(EXIT_FAILURE);
        }

}

//void getPath do later after bfs
void getPath(List L, Graph G, int u){
	if(getSource(G) != NIL){
		if(u == getSource(G)){
			append(L, u);
		}else if(getParent(G,u) == NIL){
			/*printf("No %d-%d path exits\n", getSource(u), u);*/
			append(L, NIL);
		}else{
			getPath(L, G, getParent(G,u));
			append(L, u);
		}
	}else{
		exit(EXIT_FAILURE);
	}
}
//void makeNULL
void makeNull(Graph G){
	for(int i = 1; i <= getOrder(G); i++){
		clear(G->adj[i]);
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
                		insertBefore(G->adj[u], v);
            		}
        	}
        	G->size++;
    	} else {
        	exit(EXIT_FAILURE);
    	}
}
/* 0 = white 1 = grey 2 = black*/
void BFS(Graph G, int s){
	int x;
	G->source = s;
	for( int i = 1; i <= getOrder(G); i++){
		G->color[i] = 0;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = 1;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List L = newList();
	append(L, s);
	while(!list_is_empty(L)){
		moveFront(L);
		x = get(L);
		deleteFront(L);
		moveFront(G->adj[x]);
		for(int j = 0; j < length(G->adj[x]); j++){
			if(G->color[get(G->adj[x])] == 0){
				G->color[get(G->adj[x])] = 1;
				G->distance[get(G->adj[x])] = G->distance[x]+1;
				G->parent[get(G->adj[x])] = x;
				append(L, get(G->adj[x]));
			}
			moveNext(G->adj[x]);
		}
		G->color[x] = 2;
	}
	freeList(&L);
}

/*** other operations ***/

void printGraph(FILE* out, Graph G){
	for( int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
	}
}
