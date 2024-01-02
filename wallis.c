#include "mathlib.h"

#include <math.h>
#include <stdio.h>
static int wallis_count = 0;

double pi_wallis(void) {
    wallis_count = 0;
    double k = 1.0;
    double factor = 0.0;
    double product_of_factors = 0.0;
    double numerator = 0.0;
    double denominator = 0.0;
    while (absolute(1.0 - factor) > EPSILON) {
        numerator = 4.0 * (k * k);
        denominator = (4.0 * (k * k)) - 1.0;
        factor = numerator / denominator;
        if (k == 1) {
            product_of_factors = factor;
        } else {
            product_of_factors *= factor;
        }
        k++;
        wallis_count++;
    }
    return product_of_factors * 2.0;
}

int pi_wallis_factors(void) {
    return wallis_count;
}
