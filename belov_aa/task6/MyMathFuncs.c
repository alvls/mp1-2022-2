#include "MyMathFuncs.h"
#include <stdio.h>
#include <Math.h>

double factorial(int x)
{
	double res = 1;
	for (int i = 2; i <= x; i++)
		res *= i;
	return res;
}
double sinus(double x, int n)
{
	if (n % 2 == 0)
		return pow(x, 2 * n + 1) / factorial(2 * n + 1);
	else
		return (-1) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
}
double cosinus(double x, int n)
{
	if (n % 2 == 0)
		return pow(x, 2 * n) / factorial(2 * n);
	else
		return (-1) * (pow(x, 2 * n) / factorial(2 * n));
}
double exponent(double x, int n)
{
	return pow(x, n) / factorial(n);
}
double sqrt_1plusx(double x, int n)
{
	if (n % 2 == 0)
		return (factorial(2 * n) / ((1 - 2 * n) * pow(factorial(n), 2) * pow(4, n))) * pow(x, n);
	else
		return (-1) * (factorial(2 * n) / ((1 - 2 * n) * pow(factorial(n), 2) * pow(4, n))) * pow(x, n);
}
