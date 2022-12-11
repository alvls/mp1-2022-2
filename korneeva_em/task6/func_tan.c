#include "math_functions.h"

double approx_tan(double x, double term, int n)
{
    n += 1; // В ряде Маклорена для тангенсов n0 = 1

    if (n == 1)
    {
        return x;
    }

    long a = pow(4, n - 1);

    return term * (((-4) * bernoulli(2 * n) * (1 - (a * 4)) * (x * x)) / (bernoulli(2 * (n - 1)) * (1 - a) * ((2 * n) - 1) * (2 * n)));

}