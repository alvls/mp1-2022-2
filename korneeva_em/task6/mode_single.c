#include "math_functions.h"
#include "console_utils.h"

void glamour_printf(const char* text, const char* format, ...)
{
	gotoxy(wnd.X / 2 - ((strlen(text) + strlen(format) * 2) / 2), wherey());

	textcolor(LIGHTGREEN);
	printf("%s", text);

	va_list vlist;
	va_start(vlist, format);
	
	textcolor(YELLOW);
	vprintf(format, vlist);

	va_end(vlist);
}

void mode_single(MathFunctionInfo* func, double x, int N, double precision)
{
	double reference = func->std_func(x);
	double term = 0, result = func->initial_value;
	int n;

	for (n = 0; n < N; n++)
	{
		term = func->approx_func(x, term, n);
		result += term;

		if (fabs(reference - result) <= precision)
		{
			n++;
			break;
		}
	}
	
	glamour_printf("��������� ��������: ", "%.10lf\n", func->std_func(x));
	glamour_printf("��������� ����������: ", "%.10lf\n", result);
	glamour_printf("����������� � ��������: ", "%.10lf\n", fabs(reference - result));
	glamour_printf("���������� ���������: ","%d\n", n);

	textcolor(LIGHTGRAY);
}