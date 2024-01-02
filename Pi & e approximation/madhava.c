#include "mathlib.h"

#include <math.h>
#include <stdio.h>
static int madhava_count = 0;

double pi_madhava(void) {
    madhava_count = 0;
    double k = 0.0;
    double term = 1.0;
    double sum_of_terms = 0.0;
    double previous_factor = 0.0;
    while (absolute(term) > EPSILON) {
        if (k == 0) {
            sum_of_terms += term;
            previous_factor = term;
            k++;
            madhava_count++;
        } else {
            term = (previous_factor * (-1.0 / 3.0)) / ((2.0 * k) + 1.0);
            sum_of_terms += term;
            previous_factor = previous_factor * (-1.0 / 3.0);
            k++;
            madhava_count++;
        }
    }

    return sqrt_newton(12.0) * sum_of_terms;
}

int pi_madhava_terms(void) {
    return madhava_count;
}
