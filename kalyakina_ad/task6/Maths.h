#include <stdio.h>
#include <math.h>

double (*choice_of_function1[11])(double);
double (*choice_of_function2[11])(double, int);

double exponent(double x, int i)
{
	return (pow(x, i) / factorial(i));
}

double sine(double x, int i)
{
	return ((pow(-1, i)) * (pow(x, (2 * i + 1))) / factorial(2 * i + 1));
}

double cosine(double x, int i)
{
	return ((pow(-1, i)) * (pow(x, (2 * i))) / factorial(2 * i));
}

double arcsine(double x, int i)
{
	return (factorial(2 * i) / (pow(2, 2 * i) * pow(factorial(i), 2) * (2 * i + 1)) * pow(x, (2 * i + 1)));
}

double logarithm(double x, int i)
{
	return (pow(-1, i) * pow(x, i + 1) / (i + 1));
}

double square_root(double x, int i)
{
	return (pow(-1, i) * factorial(2 * i) * pow(x, i) / ((1 - 2 * i) * pow(factorial(i), 2) * pow(4, i)));
}

double arctangent(double x, int i)
{
	return (pow(-1, i) * pow(x, 2 * i + 1) / (2 * i + 1));
}

double hyperbolic_sine(double x, int i)
{
	return (pow(x, 2 * i + 1) / factorial(2 * i + 1));
}

double hyperbolic_cosine(double x, int i)
{
	return (pow(x, 2 * i) / factorial(2 * i));
}

double hyperbolic_arcsine(double x, int i)
{
	return (pow(-1, i) * factorial(2 * i) * pow(x, 2 * i + 1) / (pow(4, i) * pow(factorial(i), 2) * (2 * i + 1)));
}

double hyperbolic_arctanget(double x, int i)
{
	return (pow(x, 2 * i + 1) / (2 * i + 1));
}

int factorial(int n)
{
	int factor = 1;
	for (; n > 1; n--)
		factor *= n;
	return factor;
}

void filling()
{
	choice_of_function1[0] = exp;
	choice_of_function2[0] = exponent;
	choice_of_function1[1] = sin;
	choice_of_function2[1] = sine;
	choice_of_function1[2] = cos;
	choice_of_function2[2] = cosine;
	choice_of_function1[3] = asin;
	choice_of_function2[3] = arcsine;
	choice_of_function1[4] = log;
	choice_of_function2[4] = logarithm;
	choice_of_function1[5] = sqrt;
	choice_of_function2[5] = square_root;
	choice_of_function1[6] = atan;
	choice_of_function2[6] = arctangent;
	choice_of_function1[7] = sinh;
	choice_of_function2[7] = hyperbolic_sine;
	choice_of_function1[8] = cosh;
	choice_of_function2[8] = hyperbolic_cosine;
	choice_of_function1[9] = asinh;
	choice_of_function2[9] = hyperbolic_arcsine;
	choice_of_function1[10] = atanh;
	choice_of_function2[10] = hyperbolic_arctanget;

}