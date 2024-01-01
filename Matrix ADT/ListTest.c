/***
 * Author: Mignot Mesele
 * Title: ListTest.c
 * Purpose: Testing file for List ADT
 * ***/

#include "List.h"

int main() {
    List myList1 = newList();
    List myList2 = newList();
    int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    append(myList1, &X[0]);
    append(myList1, &X[1]);
    append(myList1, &X[2]);

    append(myList2, &X[3]);
    append(myList2, &X[4]);
    append(myList2, &X[5]);

    moveFront(myList1);
    moveNext(myList1);
    moveNext(myList1);

    moveBack(myList2);
    movePrev(myList2);
    movePrev(myList2);

    printf("Front of myList1: %d\n", *(int*)front(myList1));
    printf("Back of myList1: %d\n", *(int*)back(myList1));
    printf("Front of myList2: %d\n", *(int*)front(myList2));
    printf("Back of myList2: %d\n", *(int*)back(myList2));

    printf("Element at cursor for myList1: %d\n", *(int*)get(myList1));
    printf("Element at cursor for myList2: %d\n", *(int*)get(myList2));

    set(myList1, &X[8]);

    moveFront(myList2);
    insertBefore(myList2, &X[6]);
    insertAfter(myList2, &X[7]);

    moveFront(myList2);
    while (index(myList2) >= 0) {
        printf("%d ", *(int*)get(myList2));
        moveNext(myList2);
    }
    printf("\n");

    deleteFront(myList2);
    deleteBack(myList2);
    moveNext(myList2);
    delete(myList2);

    List myListConcat = concatList(myList1, myList2);

    moveFront(myListConcat);
    while (index(myListConcat) >= 0) {
        printf("%d ", *(int*)get(myListConcat));
        moveNext(myListConcat);
    }
    printf("\n");

    freeList(&myList1);
    freeList(&myList2);
    freeList(&myListConcat);

    return 0;
}
