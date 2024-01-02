#include "mathlib.h"

#include <stdio.h>
static int viete_count = 0;

double pi_viete(void) {
    viete_count = 0;
    int k = 1;
    double factor = 0.0;
    double previous_factor = 0.0;
    double sqrt = 0.0;
    double product_of_factor = 0.0;
    while (absolute(1.0 - factor) > EPSILON) {
        if (k == 1) {
            sqrt = 2.0 + previous_factor;
            factor = sqrt_newton(sqrt) / 2.0;
            product_of_factor += factor;
            previous_factor = sqrt_newton(sqrt);
            k++;
            viete_count++;
        } else {
            sqrt = 2.0 + previous_factor;
            factor = (sqrt_newton(sqrt) / 2.0);
            product_of_factor *= factor;
            previous_factor = sqrt_newton(sqrt);
            k++;
            viete_count++;
        }
    }
    return (2.0 / product_of_factor);
}
int pi_viete_factors(void) {
    return viete_count;
}
