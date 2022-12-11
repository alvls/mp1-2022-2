#pragma once

// sigma * (x^(2n))/(2n)!)

double approx_cosh(double x, double term, int n)
{
    if (n == 0)
    {
        return 1;
    }
    return term * ((x * x) / (((2 * n) - 1) * (2 * n)));
}