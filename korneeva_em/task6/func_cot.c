#include "math_functions.h"

double approx_cot(double x, double term, int n)
{
    if (n == 0)
    {
        return 1 / x;
    }

    if (n == 1)
    {
        term *= -1;
    }

    return term * ((4 * bernoulli(2 * n) * (x * x)) / (((2 * n) - 1) * (2 * n) * bernoulli(2 * (n - 1))));
}