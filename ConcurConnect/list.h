
#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListObj *List;

typedef void *ListElement;

List newList(void);
void freeList(List *pL);
int length(List L);
int ind(List L);
ListElement front(List L);
ListElement back(List L);
void *get(List L);
void clear(List L);
void set(List L, ListElement x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, ListElement x);
void append(List L, ListElement x);
void insertBefore(List L, ListElement x);
void insertAfter(List L, ListElement x);
void deleteFront(List L);
void deleteBack(List L);
void delete (List L);
List concatList(List A, List B);
bool list_is_empty(List L);
#endif
