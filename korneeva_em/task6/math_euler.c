#include "math_functions.h"
#include "calc_modes.h"

long long euler_numbers[NMAX_MAX * 2 / 2] = { 1, -1 };
int calculated_euler_numbers = 1;

//https://math.stackexchange.com/questions/905310/calculating-eulers-numbers 

// Начиная с n=14, они начинают немного отличаться
// от табличных значений
long long calculate_euler_number(int n)
{
    long long result = 0;

    for (int k = 1; k < n; k++)
    {
        result += binomial_coefficient(2 * n, 2 * k) * euler(2 * k);
    }

    result *= n % 2 == 0 ? 1 : -1;
    result += n % 2 == 0 ? 1 : -1; // = pow(-1, n)

    result *= sign(euler(2 * (n - 1)));

    euler_numbers[n] = result;
    calculated_euler_numbers++;

    return result;
}

long long euler(int n)
{
    if (n % 2 != 0)
    {
        return 0;
    }

    n /= 2;

    if (n <= calculated_euler_numbers)
    {
        return euler_numbers[n];
    }

    return calculate_euler_number(n);
}