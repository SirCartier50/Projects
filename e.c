#include "mathlib.h"

#include <stdio.h>
static int term_count = 0;
double e(void) {
    term_count = 0;
    int k = 0;
    double term = 1.0;
    double previous_term = 1.0;
    double sum_of_terms = 0.0;
    while (absolute(term) > EPSILON) {
        if (k == 0) {
            sum_of_terms += term;
            k++;
        } else if (k == 1) {
            term = 1;
            sum_of_terms += term;
            k++;
            term_count++;
        } else {
            term = (1.0 / k) * (previous_term);
            sum_of_terms += term;
            previous_term = term;
            k++;
            term_count++;
        }
    }
    return sum_of_terms;
}
int e_terms(void) {
    return term_count;
}
