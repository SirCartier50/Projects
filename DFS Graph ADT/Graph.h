/***
 * Author: Mignot Mesele
 * Title: Graph.h
 * Purpose: Header file for Graph ADT
 ***/
#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#include "List.h"
#define UNDEF -1
#define NIL 0

typedef struct GraphObj* Graph;


/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void makeNull(Graph G);
void DFS(Graph G, List s);
void Visit(Graph G,List s, int u, int* time);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif

