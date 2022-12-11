#include "math_functions.h"

double approx_csc(double x, double term, int n)
{
    if (n == 0)
    {
        return 1 / x;
    }

    return (term * (-1) * (pow(2, (2 * n) - 1) - 1) * bernoulli(2 * n) * (x * x)) / (((2 * n) - 1) * (2 * n) * ((pow(2, (2 * n) - 3) - 1) * bernoulli(2 * (n - 1))));
}