/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{3}
 * List.c
 * List ADT
 ***/

#include "List.h"

typedef struct NodeObj *Node;

typedef struct NodeObj {
  int data;
  Node next;
  Node prev;
} NodeObj;

typedef struct ListObj {
  int length;
  Node front;
  Node back;
  int index;
  Node cursor;
} ListObj;

Node newnode(int data) {
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = N->prev = NULL;
  return N;
}

void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}
List newList(void) {
  List new_list = malloc(sizeof(ListObj));
  new_list->front = new_list->back = NULL;
  new_list->length = 0;
  new_list->index = -1;
  new_list->cursor = NULL;
  return new_list;
}

void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    if (!list_is_empty(*pL)) {
      clear(*pL);
    }
    free(*pL);
    *pL = NULL;
  }
}

int length(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  return L->length;
}

int index(List L) {
  if (L->cursor != NULL && L->index >= 0) {
    return L->index;
  } else {
    return -1;
  }
}

int front(List L) {
  if (L->length > 0) {
    return (L->front->data);
  } else {
    exit(EXIT_FAILURE);
  }
}

bool list_is_empty(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  return (L->length == 0);
}

int back(List L) {
  if (L->length > 0) {
    return (L->back->data);
  } else {
    exit(EXIT_FAILURE);
  }
}

int get(List L) {
  if ((L->length > 0) && (L->index >= 0)) {
    return L->cursor->data;
  } else {
    exit(EXIT_FAILURE);
  }
}

bool equals(List A, List B) {
  if (A == NULL || B == NULL) {
    exit(EXIT_FAILURE);
  }
  bool eq;
  Node C, D;

  eq = (A->length == B->length);
  C = A->front;
  D = B->front;
  while (eq && C != NULL) {
    eq = (C->data == D->data);
    C = C->next;
    D = D->next;
  }
  return eq;
}
void clear(List L) {
    if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  while (L->front != NULL) {
    deleteFront(L);
  }
}
void set(List L, int x) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  if ((L->length == 0) || (L->index < 0)) {
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
}
void moveFront(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    L->cursor = L->front;
    L->index = 0;
  }
}
void moveBack(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    L->cursor = L->back;
    L->index = L->length - 1;
  }
}
void movePrev(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  if (((L->cursor != NULL) && (L->index >= 0)) && (L->cursor != L->front)) {
    L->cursor = L->cursor->prev;
    L->index -= 1;

  } else if (((L->cursor != NULL) && (L->index >= 0)) &&
             (L->cursor == L->front)) {
    L->cursor = NULL;
    L->index = -1;
  }
}
void moveNext(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  if (((L->cursor != NULL) && (L->index >= 0)) && (L->cursor != L->back)) {
    L->cursor = L->cursor->next;
    L->index += 1;
  } else if (((L->cursor != NULL) && (L->index >= 0)) &&
             (L->cursor == L->back)) {
    L->cursor = NULL;
    L->index = -1;
  }
}
void prepend(List L, int x) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  Node N = newnode(x);
  if (list_is_empty(L)) {
    L->front = L->back = N;
  } else {

    L->front->prev = N;
    N->next = L->front;
    L->front = N;
  }
  L->length++;
  L->index++;
}
void append(List L, int x) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  Node N = newnode(x);
  if (list_is_empty(L)) {
    L->front = L->back = N;
  } else {
    L->back->next = N;
    N->prev = L->back;
    L->back = N;
  }
  L->length++;
}
void insertBefore(List L, int x) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  Node N = newnode(x);
  if ((L->length > 0) &&
      (L->index >=
       0)) {
    if (L->cursor->prev != NULL) {
      L->cursor->prev->next = N;
      N->prev = L->cursor->prev;
    } else {
      L->front = N;
    }
    N->next = L->cursor;
    L->cursor->prev = N;
    L->length++;
    L->index++;
  } else {
    exit(EXIT_FAILURE);
  }
}
void insertAfter(List L, int x) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  Node N = newnode(x);
  if ((L->length > 0) &&
      (L->index >=
       0)) {
    if (L->cursor->next != NULL) {
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
    } else {
      L->back = N;
    }
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length++;
  }
}
void deleteFront(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    Node temp = L->front;
    if (L->length > 1) {
      L->front = L->front->next;
      L->front->prev = NULL;

    } else {
      L->front = L->back = NULL;
    }
    if (L->index >= 0) {
      L->index--;
    }
    freeNode(&temp);
    temp = NULL;
    L->length--;
  }
}
void deleteBack(List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }
  if (L->length > 0) {
    Node temp = L->back;
    if (L->length > 1) {
      L->back = L->back->prev;
      L->back->next = NULL;
    } else {
      L->front = L->back = NULL;
    }
    if (L->index == (L->length - 1)) {
      L->index = -1;
    }
    L->length--;
    freeNode(&temp);
    temp = NULL;
  }
}
void delete (List L) {
  if (L == NULL) {
    exit(EXIT_FAILURE);
  }

  if ((L->length > 0) && (L->index >= 0)) {
    Node temp = L->cursor;
    if (L->cursor == L->front) {
      L->front = L->cursor->next;
      L->front->prev = NULL;
    } else if (L->cursor == L->back) {
      L->back = L->cursor->prev;
      L->back->next = NULL;

    } else {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
    }
    L->index = -1;
    L->length--;
    freeNode(&temp);
    L->cursor = NULL;
  }
}

void printList(FILE *out, List L) {

  for (Node N = L->front; N != NULL; N = N->next) {
    fprintf(out, "%d ", N->data);
  }
  fprintf(out, "\n");
}
List copyList(List L) {
  List Q = newList();
  Node temp = L->front;
  while (temp != NULL) {
    append(Q, temp->data);
    temp = temp->next;
  }
  return Q;
}
List concatList(List A, List B) {
  List C = newList();
  Node temp = A->front;
  Node D = B->front;
  while (temp != NULL) {
    append(C, temp->data);
    temp = temp->next;
  }
  while (D != NULL) {
    append(C, D->data);
    D = D->next;
  }
  return C;
}


