#include "mathlib.h"

#include <stdio.h>
static int euler_count = 0;

double pi_euler(void) {
    euler_count = 0;
    int k = 1;
    double term = 1.0;
    double pi = 0.0;
    double sum_of_terms = 0.0;
    double factor = 0.0;
    while (absolute(term) > EPSILON) {
        factor = (1.0 / k);
        term = factor * factor;
        sum_of_terms += term;
        k++;
        euler_count++;
    }
    sum_of_terms *= 6.0;
    pi = sqrt_newton(sum_of_terms);
    return pi;
}

int pi_euler_terms(void) {
    return euler_count;
}
