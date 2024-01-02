#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MASK    ((1 << 30) - 1)
#define OPTIONS "aishqbr:n:p:H"
void help_message(void) {
    printf("SYNOPSIS\n A collection of comparison-based sorting algorithms.\nUSAGE\n   "
           "./sorting-x86 [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n   -H         "
           "     Display program help and usage.\n   -a              Enable all sorts.\n   -h      "
           "        Enable Heap Sort.\n   -b              Enable Batcher Sort.\n   -s              "
           "Enable Shell Sort.\n   -q              Enable Quick Sort.\n   -i              Enable "
           "Insertion Sort.\n   -n length       Specify number of array elements (default: 100).\n "
           "  -p elements     Specify number of elements to print (default: 100).\n   -r seed      "
           "   Specify random seed (default: 13371453).\n");
}
void fill_array(uint32_t *A, uint32_t n, long int seed) {
    srandom(seed);
    for (uint32_t i = 0; i < n; i++) {
        A[i] = random() & MASK;
    }
}
int main(int argc, char **argv) {
    int flag_h = 0;
    int flag_n = 0;
    int flag_r = 0;
    int flag_p = 0;
    enum Sort { INSERT, SHELL, HEAP, QUICK, BATCHER };
    long int default_element = 100;
    long int default_seed = 13371453;
    long int default_size = 100;
    Set A = set_empty();
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': A = set_universal(); break;
        case 'i': A = set_insert(A, INSERT); break;
        case 's': A = set_insert(A, SHELL); break;
        case 'h': A = set_insert(A, HEAP); break;
        case 'q': A = set_insert(A, QUICK); break;
        case 'b': A = set_insert(A, BATCHER); break;
        case 'r':
            flag_r = 1;
            default_seed = strtoul(optarg, NULL, 10);
            break;
        case 'n':
            flag_n = 1;
            default_size = strtoul(optarg, NULL, 10);
            break;
        case 'p':
            flag_p = 1;
            default_element = strtoul(optarg, NULL, 10);
            break;
        case 'H': flag_h = 1; break;
        }
    }
    uint32_t *arr = calloc(default_size, sizeof(uint32_t));
    Stats stats;
    if (default_element > default_size) {
        default_element = default_size;
    }
    if (set_member(A, INSERT)) {
        reset(&stats);
        fill_array(arr, default_size, default_seed);
        insertion_sort(&stats, arr, default_size);
        print_stats(&stats, "Insertion Sort", default_size);
        for (uint32_t i = 0; i < default_element; i++) {
            printf("%13" PRIu32, arr[i]);
            if (i % 5 == 4 || i % 5 == (default_element - 1) % 5) {
                printf("\n");
            }
        }
    }
    if (set_member(A, HEAP)) {
        reset(&stats);
        fill_array(arr, default_size, default_seed);
        heap_sort(&stats, arr, default_size);
        print_stats(&stats, "Heap Sort", default_size);
        for (uint32_t i = 0; i < default_element; i++) {
            printf("%13" PRIu32, arr[i]);
            if (i % 5 == 4 || i % 5 == (default_element - 1) % 5) {
                printf("\n");
            }
        }
    }

    if (set_member(A, SHELL)) {
        reset(&stats);
        fill_array(arr, default_size, default_seed);
        shell_sort(&stats, arr, default_size);
        print_stats(&stats, "Shell Sort", default_size);
        for (uint32_t i = 0; i < default_element; i++) {
            printf("%13" PRIu32, arr[i]);
            if (i % 5 == 4 || i % 5 == (default_element - 1) % 5) {
                printf("\n");
            }
        }
    }
    if (set_member(A, QUICK)) {
        reset(&stats);
        fill_array(arr, default_size, default_seed);
        quick_sort(&stats, arr, default_size);
        print_stats(&stats, "Quick Sort", default_size);
        for (uint32_t i = 0; i < default_element; i++) {
            printf("%13" PRIu32, arr[i]);
            if (i % 5 == 4 || i % 5 == (default_element - 1) % 5) {
                printf("\n");
            }
        }
    }
    if (set_member(A, BATCHER)) {
        reset(&stats);
        fill_array(arr, default_size, default_seed);
        batcher_sort(&stats, arr, default_size);
        print_stats(&stats, "Batcher Sort", default_size);
        for (uint32_t i = 0; i < default_element; i++) {
            printf("%13" PRIu32, arr[i]);
            if (i % 5 == 4 || i % 5 == (default_element - 1) % 5) {
                printf("\n");
            }
        }
    }
    if (flag_h == 1) {
        help_message();
    }
    if (set_member(A, INSERT) == false && set_member(A, HEAP) == false
        && set_member(A, SHELL) == false && set_member(A, QUICK) == false
        && set_member(A, BATCHER) == false && flag_r == 0 && flag_p == 0 && flag_n == 0
        && flag_h == 0) {
        help_message();
    }
    free(arr);
    return 0;
}
