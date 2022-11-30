#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include "Header.h"
#include "omp.h"
#include <time.h>


static long long factorial(int x)
{
	long long f;
	for (f = 1; x > 1; f *= (x--))
		;
	return f;
}

void sinus(double x, double pog, int n, int mode)
{
	double a = 0;
	int count = 0;
	do
	{
		a += pow((-1), count) * ((pow(x, 2 * count + 1)) / factorial(2 * count + 1));
		count++;
	} while ((fabs(sin(x) - a) > pog) && (count < n));
	if (mode == 1)
		printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", sin(x), a, sin(x) - a, count);
	else if (mode == 2)
		printf("%16lf%24lf%26lf\n", sin(x), a, fabs(sin(x) - a));
}

void cosinus(double x, double pog, int n, int mode)
{
	double a = 0;
	int count = 0;
	do
	{
		a += pow((-1), count) * ((pow(x, 2 * count)) / factorial(2 * count));
		count++;
	} while ((fabs(cos(x) - a) > pog) && (count < n));
	if (mode == 1)
		printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", cos(x), a, fabs(cos(x) - a), count);
	else
		printf("%16lf%24lf%26lf\n", cos(x), a, fabs(cos(x) - a));
}

void exponenta(double x, double pog, int n, int mode)
{
	double a = 0;
	int count = 0;
	do
	{

		a += pow(x, count) / factorial(count);
		count++;
	} while ((fabs(exp(x) - a) > pog) && (count < n));
	if (mode == 1)
		printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", exp(x), a, fabs(exp(x) - a), count);
	else
		printf("%16lf%24lf%26lf\n", exp(x), a, fabs(exp(x) - a));
}

double num_eiler(int n)
{
	double E = 0;
	int count = 0;
	do
	{
		E += 1 / factorial(count);
		count++;
	} while (count < n);
}
void secans(double x, double pog, int n, int mode)
{
	double a = 0;
	int count = 0, last = 1;
	do
	{
		if (count % 2 == 0)
			a += (num_eiler(2 * count) * pow(x, 2 * count)) / factorial(2 * count);
		else
			a += ((-1) * num_eiler(2 * count) * pow(x, 2 * count)) / factorial(2 * count);
		count++;
	} while ((fabs((1 / cos(x)) - a) > pog) && (count < n));
	if (mode == 1)
		printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", 1 / cos(x), a, fabs((1 / cos(x)) - a), count);
	else
		printf("%16lf%24lf%26lf\n", 1 / cos(x), a, fabs(1 / cos(x) - a));
}

void sh(double x, double pog, int n, int mode)
{

	double a = 0, answer = (exp(x) - exp((-1) * x) / 2);
	int count = 0;
	do
	{
		a += pow(x, 2 * count + 1) / factorial(2 * count + 1);
		count++;
	} while ((fabs(answer - a) > pog) && (count < n));
	if (mode == 1)
		printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", answer, a, fabs(answer - a), count);
	else
		printf("%16lf%24lf%26lf\n", answer, a, fabs(answer - a));
}

void ch(double x, double pog, int n, int mode)
{
	double a = 0, answer = (exp(x) + exp((-1) * x) / 2);
	int count = 0;
	do
	{
		a += pow(x, 2 * count) / factorial(2 * count);
		count++;
	} while ((fabs(answer - a) > pog) && (count < n));
	if (mode == 1)
		printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", answer, a, fabs(answer - a), count);
	else
		printf("%16lf%24lf%26lf\n", answer, a, fabs(answer - a));
}

void ln(double x, double pog, int n, int mode)
{
	double a = 0;
	int count = 1;
	do
	{
		if (count % 2 == 0)
			a += (-1) * pow(x, count) / factorial(count);
		else
			a += pow(x, count) / factorial(count);
		count++;
	} while ((fabs(log(x) - a) > pog) && (count < n));
	if (mode == 1)
		printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", log(x), a, fabs(log(x) - a), count);
	else
		printf("%16lf%24lf%26lf\n", log(x), a, fabs(log(x) - a));
}