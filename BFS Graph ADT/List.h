/***
 * Mgnot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{2}
 * List.h
 * Header file for List ADT
 ***/
#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListObj *List;

typedef int ListElement;

List newList(void);
void freeList(List *pL);
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete (List L);
void printList(FILE *out, List L);
List copyList(List L);
List concatList(List A, List B);
bool list_is_empty(List L);
#endif
