#include "insert.h"

#include <stdio.h>
#include <stdlib.h>
/*define mask ((1<<30)-1)
 * define enum sort={HEAP, BATCHER, INSERT, SHELL, QUICK}
 * populate_array(A, n, s){
 * srandom(s);
 * loop 0-n{
 * a[i]=random()&mask
 * }
 * }
 *
 * while getopt and handle command options with sets
 * array=calloc(n,sizeof(uint32_t))
 * if(set_member(HEAP)){
 * populate(array, n=size, seed=s)
 * heap_Sort(stat variable, ,n)
 * print_array()
 * do this for every sort
 * free()*/
void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    uint32_t j;
    uint32_t temp;
    for (uint32_t k = 1; k < length; k++) {
        j = k;
        temp = move(stats, arr[k]);
        while (j > 0 && (cmp(stats, temp, arr[j - 1]) < 0)) {
            arr[j] = move(stats, arr[j - 1]);
            j -= 1;
        }
        arr[j] = move(stats, temp);
    }
}
