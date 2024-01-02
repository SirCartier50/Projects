#include "shell.h"

#include "gaps.h"

#include <stdio.h>
#include <stdlib.h>
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t temp = 0;
    uint32_t j = 0;
    for (uint32_t gap = 0; gap < GAPS; gap++) {
        for (uint32_t i = gaps[gap]; i < n; i++) {
            j = i;
            temp = move(stats, A[i]);
            while (j >= gaps[gap] && (cmp(stats, temp, A[j - gaps[gap]]) < 0)) {
                A[j] = move(stats, A[j - gaps[gap]]);
                j -= gaps[gap];
            }
            A[j] = move(stats, temp);
        }
    }
}
