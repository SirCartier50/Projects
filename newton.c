#include "mathlib.h"

#include <stdio.h>
static int sqrt_count = 0;
double sqrt_newton(double base) {
    sqrt_count = 0;
    double guess = 1.0;
    double previous_guess = 0.0;
    while (absolute(guess - previous_guess) > EPSILON) {
        previous_guess = guess;
        guess = 0.5 * (guess + (base / guess));
        sqrt_count++;
    }
    return guess;
}

int sqrt_newton_iters() {
    return sqrt_count;
}
