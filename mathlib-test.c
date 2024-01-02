#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvwnhs :"

int help_message(void) {
    printf(
        "This is a test harness for the small numerical library. Your input shoud be in the "
        "format, ./{filename} -{aebmrvnsh}. To run all tests, you'd use the -a option. To run run "
        "e approximation test, use -e option. To run Bailey-Borwein-Plouffe pi approximation test, "
        "use -b option. To run Madhava pi approximation test, use -m option. To run Euler sequence "
        "pi approximation test, use -r option. To run Viete pi approximation test, use -v option. "
        "To run Wallis pi approximation test, run -w option. To run Newton-Raphson square root "
        "approximation test, run -n. To show all of the test's amount of terms, use -s. The -h "
        "option displays the help message. These options can only run once, meaning that if you "
        "put ./mathlib-test -a -e -v, ./mathlib-test -b -m -a, or ./mathlib-test -e -e, it would "
        "basically ignore the second request to run the test.\n");
    return 0;
}
int main(int argc, char **argv) {
    int opt = ' ';
    double diff = 0.0;
    int flag_a = 0;
    int flag_e = 0;
    int flag_b = 0;
    int flag_m = 0;
    int flag_r = 0;
    int flag_v = 0;
    int flag_w = 0;
    int flag_n = 0;
    int flag_s = 0;
    int flag_h = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': flag_a = 1; break;
        case 'e': flag_e = 1; break;
        case 'b': flag_b = 1; break;
        case 'm': flag_m = 1; break;
        case 'r': flag_r = 1; break;
        case 'v': flag_v = 1; break;
        case 'w': flag_w = 1; break;
        case 'n': flag_n = 1; break;
        case 's': flag_s = 1; break;
        case 'h': flag_h = 1; break;
        }
    }

    if (flag_a == 1) {
        flag_e = 1;
        flag_b = 1;
        flag_m = 1;
        flag_r = 1;
        flag_v = 1;
        flag_w = 1;
        flag_n = 1;
    }
    if (flag_e == 1) {
        diff = M_E - e();
        printf("e() = %.15lf, M_E = %.15lf, diff = %.15lf\n", e(), M_E, diff);
        if (flag_s == 1) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (flag_b == 1) {
        diff = M_PI - pi_bbp();
        printf("pi_bbp() = %.15lf, M_PI = %.15lf, diff = %.15lf\n", pi_bbp(), M_PI, diff);
        if (flag_s == 1) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (flag_m == 1) {
        diff = M_PI - pi_madhava();
        printf("pi_madhava() = %.15lf, M_PI = %.15lf, diff = %.15lf\n", pi_madhava(), M_PI, diff);
        if (flag_s == 1) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (flag_r == 1) {
        diff = M_PI - pi_euler();
        printf("pi_euler() = %.15lf, M_PI = %.15lf, diff = %.15lf\n", pi_euler(), M_PI, diff);
        if (flag_s == 1) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (flag_v == 1) {
        diff = M_PI - pi_viete();
        printf("pi_viete() = %.15lf, M_PI = %.15lf, diff = %.15lf\n", pi_viete(), M_PI, diff);
        if (flag_s == 1) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (flag_w == 1) {
        diff = M_PI - pi_wallis();
        printf("pi_wallis() = %.15lf, M_PI = %.15lf, diff = %.15lf\n", pi_wallis(), M_PI, diff);
        if (flag_s == 1) {
            printf("pi_wallis() terms = %d\n", pi_wallis_factors());
        }
    }
    if (flag_n == 1) {
        for (double d = 0.0; d <= 9.95; d += 0.1) {
            printf("sqrt_newton(%.2lf) = %16.15lf, sqrt(%.2lf) = %16.15lf, diff = %16.15lf\n", d,
                sqrt_newton(d), d, sqrt(d), sqrt(d) - sqrt_newton(d));
            if (flag_s == 1) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
    if (flag_a == 0 && flag_e == 0 && flag_b == 0 && flag_m == 0 && flag_r == 0 && flag_v == 0
        && flag_w == 0 && flag_n == 0 && flag_s == 1 && flag_h == 0) {
        help_message();
    }
    if (flag_h == 1) {
        help_message();
    }

    if (flag_a == 0 && flag_e == 0 && flag_b == 0 && flag_m == 0 && flag_r == 0 && flag_v == 0
        && flag_w == 0 && flag_n == 0 && flag_s == 0 && flag_h == 0) {
        help_message();
    }
}
