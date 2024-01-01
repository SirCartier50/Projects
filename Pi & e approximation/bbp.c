#include "mathlib.h"

#include <stdio.h>
static int bbp_count = 0;

double pi_bbp(void) {
    bbp_count = 0;
    int k = 0;
    double term = 1.0;
    double sum_of_terms = 0.0;
    double previous_factor = 1.0 / 16.0;
    double sixteenth = 1.0 / 16.0;
    while (absolute(term) > EPSILON) {
        if (k == 0) {
            term = ((4.0 / ((8.0 * k) + 1.0)) - (2.0 / ((8.0 * k) + 4.0))
                    - (1.0 / ((8.0 * k) + 5.0)) - (1.0 / ((8.0 * k) + 6.0)));
            sum_of_terms += term;
            k++;
            bbp_count++;
        } else if (k == 1) {
            term = previous_factor
                   * ((4.0 / ((8.0 * k) + 1.0)) - (2.0 / ((8.0 * k) + 4.0))
                       - (1.0 / ((8.0 * k) + 5.0)) - (1.0 / ((8.0 * k) + 6.0)));
            sum_of_terms += term;
            k++;
            bbp_count++;
        }

        else {
            previous_factor = previous_factor * sixteenth;
            term = (previous_factor)
                   * ((4.0 / ((8.0 * k) + 1.0)) - (2.0 / ((8.0 * k) + 4.0))
                       - (1.0 / ((8.0 * k) + 5.0)) - (1.0 / ((8.0 * k) + 6.0)));
            sum_of_terms += term;
            k++;
            bbp_count++;
        }
    }
    return sum_of_terms;
}

int pi_bbp_terms(void) {
    return bbp_count;
}
