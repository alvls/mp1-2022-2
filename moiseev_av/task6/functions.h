#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define MAXCALC 500
#define MINCALC 20

extern HWND output_n, output_x, output_dif, hwnd, standard;
extern int number_of_func, mode, n, Nmax;
extern double dif, x, precision;
extern char text[MAXCALC];
double sum, current;

int hyperbolic()
{
	if (number_of_func % 2 != 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int comporator()
{
	if (mode == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void output(int n, double dif, int(*m)())
{
	if (!m())
	{
		sprintf_s(text, MINCALC, "%d", n);
		output_n = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 253, 35 + 20 * n, 20, 20, hwnd, NULL, NULL, NULL);

		sprintf_s(text, MAXCALC, "%lf", sum);
		output_x = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 433, 35 + 20 * n, 152, 20, hwnd, NULL, NULL, NULL);

		sprintf_s(text, MAXCALC, "%lf", dif);
		output_dif = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 603, 35 + 20 * n, 152, 20, hwnd, NULL, NULL, NULL);
	}

	else
	{
		output_x = CreateWindow("static", "Полученное значение:\n", WS_VISIBLE | WS_CHILD, 253, 50, 200, 20, hwnd, NULL, NULL, NULL);
		sprintf_s(text, MAXCALC, "%lf", sum);
		output_x = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 253, 70, 500, 20, hwnd, NULL, NULL, NULL);

		output_dif = CreateWindow("static", "Разница между эталоном и полученным значением:\n", WS_VISIBLE | WS_CHILD, 253, 110, 400, 20, hwnd, NULL, NULL, NULL);
		sprintf_s(text, MAXCALC, "%lf", dif);
		output_dif = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 253, 130, 500, 20, hwnd, NULL, NULL, NULL);

		output_n = CreateWindow("static", "Количество слагаемых:", WS_VISIBLE | WS_CHILD, 253, 170, 500, 20, hwnd, NULL, NULL, NULL);
		sprintf_s(text, MINCALC, "%d", n);
		output_n = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 253, 190, 50, 20, hwnd, NULL, NULL, NULL);
	}
}

double sin_func(int(*hyp)(), int(*m)())
{
	double(*f)(double x) = hyp() == 1 ? sinh : sin;

	sum = x;
	current = x;

	if (!m())
	{
		output(n, fabs(sum - f(x)), m);
	}

	for (n = 2; n <= Nmax; n++)
	{
		if (m())
		{
			if (fabs(sum - f(x)) <= precision)
			{
				output(n - 1, fabs(sum - f(x)), m);
				break;
			}
		}

		current = current * hyp() * ((x * x) / ((2 * (double)n - 2) * (2 * (double)n - 1)));
		sum += current;

		if (!m())
		{
			output(n, fabs(sum - f(x)), m);
		}
	}

	if (m() && fabs(sum - f(x)) > precision)
	{
		output(Nmax, fabs(sum - f(x)), m);
	}

	sprintf_s(text, MAXCALC, "%lf", f(x));
	SetWindowText(standard, text);

	return 0;
}

double cos_func(int(*hyp)(), int(*m)())
{
	double(*f)(double x) = hyp() == 1 ? cosh : cos;

	sum = 1;
	current = 1;

	if (!m())
	{
		output(n, fabs(sum - f(x)), m);
	}

	for (n = 2; n <= Nmax; n++)
	{
		if (m())
		{
			if (fabs(sum - f(x)) <= precision)
			{
				output(n - 1, fabs(sum - f(x)), m);
				break;
			}
		}

		current = current * hyp() * (x * x / ((2 * (double)n - 3) * (2 * (double)n - 2)));
		sum += current;

		if (!m())
		{
			output(n, fabs(sum - f(x)), m);
		}
	}

	if (m() && fabs(sum - f(x)) > precision)
	{
		output(Nmax, fabs(sum - f(x)), m);
	}

	sprintf_s(text, MAXCALC, "%lf", f(x));
	SetWindowText(standard, text);

	return 0;
}

double exp_func(int(*hyp)(), int(*m)())
{
	sum = 1;
	current = 1;

	if (!m())
	{
		output(n, fabs(sum - exp(x)), m);
	}

	for (n = 1; n < Nmax; n++)
	{
		if (m())
		{
			if (fabs(sum - exp(x)) <= precision)
			{
				output(n + 1, fabs(sum - exp(x)), m);
				break;
			}
		}

		current = current * x / n;
		sum += current;

		if (!m())
		{
			output(n + 1, fabs(sum - exp(x)), m);
		}
	}

	if (m() && fabs(sum - exp(x)) > precision)
	{
		output(Nmax, fabs(sum - exp(x)), m);
	}

	sprintf_s(text, MAXCALC, "%lf", exp(x));
	SetWindowText(standard, text);

	return 0;
}