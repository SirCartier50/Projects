#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct ListElement ListElement;
struct ListElement {
    Node *tree;
    ListElement *next;
};
struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));
    return pq;
}
void pq_free(PriorityQueue **q) {
    free(*q);
    *q = NULL;
}
bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL) {
        return true;
    }
    return false;
}

bool pq_size_is_1(PriorityQueue *q) {
    if (q->list == NULL) {
        return false;
    }
    if (q->list->tree != NULL && q->list->next == NULL) {
        return true;
    }
    return false;
}
bool pq_less_than(Node *n1, Node *n2) {
    if (n1->weight < n2->weight)
        return true;
    if (n1->weight > n2->weight)
        return false;
    return n1->symbol < n2->symbol;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *e = calloc(1, sizeof(ListElement));
    e->tree = tree;
    ListElement *previous = NULL;
    ListElement *current = q->list;
    if (pq_is_empty(q)) {
        q->list = e;
        return;
    }
    if (pq_less_than(e->tree, current->tree)) {
        e->next = current;
        q->list = e;
        return;
    }
    while (current != NULL) {
        if (pq_less_than(e->tree, current->tree)) {
            e->next = current;
            previous->next = e;
            return;
        }
        previous = current;
        current = current->next;
    }
    previous->next = e;
}

bool dequeue(PriorityQueue *q, Node **tree) {
    if (pq_is_empty(q)) {
        return false;
    } else {
        ListElement *e = q->list;
        q->list = q->list->next;
        *tree = e->tree;
        free(e);
        e = NULL;
        return true;
    }
}
void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree, '<', 2);
        e = e->next;
    }
    printf("=============================================\n");
}
