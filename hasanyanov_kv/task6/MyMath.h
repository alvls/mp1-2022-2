#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include "Header.h"
#include "omp.h"
#include <time.h>

void myprint(double a, double b, int count)
{
	gotoxy(0, count + 1);
	printf("%d)", count);
	gotoxy(11, wherey());
	printf("%lf", a);
	gotoxy(35, wherey());
	printf("%lf", b);
	gotoxy(61, wherey());
	printf("%lf", fabs(a - b));
	gotoxy(0, wherey() + 1);
}
void myprintf(double a, double b, int count)
{
	printf("Эталонное значение: %lf\nРассчитанное значение: %lf\nПогрешность: %lf\nКоличество слагаемых: %d\n", a, b, fabs(a - b), count);
}

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
		myprintf(sin(x), a, count);
	else
		myprint(sin(x), a, count);
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
		myprintf(cos(x), a, count);
	else
		myprint(cos(x), a, count);
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
		myprintf(exp(x), a, count);
	else
		myprint(exp(x), a, count);
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
	return E;
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
		myprintf(1 / cos(x), a, count);
	else
		myprint(1 / cos(x), a, count);
}

void sh(double x, double pog, int n, int mode)
{

	double a = 0, answer = (exp(x) - exp((-1) * x) / 2);
	int count = 0;
	do
	{
		a += pow(x, 2 * count + 1) * (1 / factorial(2 * count + 1));
		count++;
	} while ((fabs(answer - a) > pog) && (count < n));
	if (mode == 1)
		myprintf(answer, a, count);
	else
		myprint(answer, a, count);
}



void ch(double x, double pog, int n, int mode)
{
	double a = 0, answer = (exp(x) + exp((-1) * x) / 2);
	int count = 0;
	do
	{
		a += pow(x, 2 * count) * (1 / factorial(2 * count));
		count++;
	} while ((fabs(answer - a) > pog) && (count < n));
	if (mode == 1)
		myprintf(answer, a, count);
	else
		myprint(answer, a, count);
}



void ln(double x, double pog, int n, int mode)
{
	double a = 0;
	int count = 0;
	do
	{
		if (count % 2 == 0)
			a += (-1) * pow(x, count) / count + 1;
		else
			a += pow(x, count) / count + 1;
		count++;
	} while ((fabs(log(x) - a) > pog) && (count < n));
	if (mode == 1)
		myprintf(log(x), a, count);
	else
		myprint(log(x), a, count);
}