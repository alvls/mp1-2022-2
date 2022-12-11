#pragma once

// sigma ((x^n) / n!)

double approx_exp(double x, double term, int n)
{
    if (n == 0)
    {
        return 1;
    }
    return term * (x / n);
}