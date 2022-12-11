#pragma once

#include "math_functions.h"
#include "console_utils.h"

void mode_serial(MathFunctionInfo* func, double x, int NMax)
{
	double term = 0, result = func->initial_value;
	int n;
	double reference = func->std_func(x);

	textcolor(LIGHTBLUE);
	gotoxy((wnd.X  - 32) / 2, wherey() + 1);
	printf("Эталонное значение: %.10lf\n", reference);
	
	textcolor(LIGHTGRAY);
	gotoxy(wnd.X / 4, wherey() + 2);
	printf("%-24s   %-24s  %-24s", "Слагаемые", "Оценка", "Расхождение");
	gotoxy(wnd.X / 4, wherey() + 1);
	printf("%-24s   %-24s  %-24s", "---------", "------------", "------------");

	for (n = 0; n < NMax; n++)
	{
		term = func->approx_func(x, term, n);
		result += term;

		textcolor(n % 2 == 0 ? DARKGRAY : WHITE);

		gotoxy(wnd.X / 4, wherey() + 1);
		printf("%-8d %30.10lf %25.10lf", n+1, result, fabs(reference - result));
	
	}
	textcolor(LIGHTGRAY);
	gotoxy(0, wherey() + 1);
}