#include "math_functions.h"

// sigma (x^(2n-1))/(2n-1)!)

double approx_sinh(double x, double term, int n)
{
    if (n == 0)
    {
        return x;
    }
    return term * ((x * x) / ((2 * n) * ((2 * n) + 1)));
}