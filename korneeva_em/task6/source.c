#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "console_utils.h"

#include "math_functions.h"
#include "math_functions_list.h"
#include "calc_modes.h"

COORD wnd;

#define ONE_PLUS "1+"
#define ONE_PLUS_LEN (sizeof(ONE_PLUS) / sizeof(char)) - 1

int extract_function_argument(char* buf, double* x)
{
	char* arg_begin = strstr(buf, "(");
	if (!arg_begin)
	{
		return 0;
	}

	char* arg_subbegin = strstr(arg_begin, ONE_PLUS);

	if (arg_subbegin)
	{
		*arg_begin = '\0';
		arg_begin = arg_subbegin + ONE_PLUS_LEN - 1;
	}


	char* arg_end = strstr(arg_begin, ")");
	if (!arg_end)
	{
		return 0;
	}

	*arg_begin++ = '\0';
	*arg_end = '\0';

	*x = atof(arg_begin);
	return 1;
}

MathFunctionInfo* find_function(const char* name)
{
	for (int i = 0; i < AVAILABLE_MATH_FUNCTIONS; i++)
	{
		if (strcmp(math_functions[i].name, name) == 0)
			return &math_functions[i];
	}

	return 0;
}

void print_header()
{
	gotoxy(0, 0);

	textcolor(CYAN);
	gotoxy((wnd.X - 29) / 2, wherey() + 1);
	printf("============================");
	gotoxy((wnd.X - 29) / 2, wherey() + 1);
	printf("     Аппроксиматор-3000     ");
	gotoxy((wnd.X - 29) / 2, wherey() + 1);
	printf("============================");

	textcolor(LIGHTGREEN);
	gotoxy((wnd.X - 26) / 2, wherey() + 2);
	printf("Список доступных функций:");

	gotoxy(0, wherey() + 1);

	for (int i = 0; i < AVAILABLE_MATH_FUNCTIONS; i++)
	{
		if (i % (AVAILABLE_MATH_FUNCTIONS / 6) == 0)
			gotoxy(0, wherey() + 1);

		textcolor(i % 2 == 0 ? LIGHTCYAN : GREEN);
		gotoxy(5 + 44 * (i % (AVAILABLE_MATH_FUNCTIONS / 6)), wherey());

		printf("%s(%s)%s", math_functions[i].name, math_functions[i].usage, math_functions[i].range);
	}

	textcolor(LIGHTGRAY);
	gotoxy(0, wherey() + 2);
}

void print_help()
{
	textcolor(LIGHTBLUE);
	gotoxy((wnd.X - 110) / 2, wherey() + 1);
	printf("Для однократного расчета введите функцию, максимальное количество слагаемых (%d-%d) и точность (>= %lf)", N_MIN, N_MAX, MIN_PRECISION);
	gotoxy((wnd.X - 93) / 2, wherey() + 1);
	printf("Для работы в режиме серийного эксперимента введите функцию и количество экспериментов (%d-%d)", NMAX_MIN, NMAX_MAX);

	textcolor(LIGHTCYAN);
	gotoxy((wnd.X - 30) / 2, wherey() + 1);
	printf("Пример ввода функции: sin(0,5)");

	textcolor(LIGHTGRAY);
	gotoxy(0, wherey() + 2);
}

void print_error(const char* text)
{
	textcolor(RED);
	gotoxy((wnd.X - strlen(text)) / 2, wherey() + 1);
	printf(text);
	gotoxy(0, wherey() + 2);
	textcolor(LIGHTGRAY);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("title Аппроксиматор-3000");

	SMALL_RECT rect;
	getwindow(&rect, &wnd);

	char buf[128];
	int read;

	char func_input[16];
	double x, precision;
	int n;

	MathFunctionInfo* func;
	print_header();

	while (1)
	{
		print_help();

		gotoxy(2, wherey());
		printf("Введите параметры: ");
		gets_s(buf, sizeof(buf));
		read = sscanf_s(buf, "%s %d %lf", func_input, sizeof(func_input), &n, &precision);

		if (read < 2 || read > 3)
		{
			print_error("Некорректный ввод");
			continue;
		}


		if (!extract_function_argument(func_input, &x))
		{
			print_error("Функция введена неверно");
			continue;
		}

		func = find_function(func_input);
		if (!func)
		{
			print_error("Функция не найдена");
			continue;
		}


		if (!func->validate_range(x))
		{
			print_error("Недопустимый аргумент");
			continue;
		}


		clrscr();
		print_header();

		textcolor(LIGHTMAGENTA);
		gotoxy((wnd.X - 36) / 2, wherey() + 1);
		printf("Расчёт функции %s(%s), x = %lf\n", func->name, func->usage, x);
		textcolor(LIGHTGRAY);

		switch (read)
		{
		case 3:
			if ((n > N_MAX) || (n < N_MIN))
			{
				print_error("Введённое количество слагаемых недопустимо");
				continue;
			}

			if (precision < MIN_PRECISION)
			{
				print_error("Введённая точность недопустима");
				continue;
			}
			textcolor(YELLOW);
			gotoxy((wnd.X - 7) / 2, wherey() + 1);
			printf("Режим 1");
			mode_single(func, x, n, precision);
			break;
		case 2:
			if ((n > NMAX_MAX) || (n < NMAX_MIN))
			{
				print_error("Введённое количество экспериментов недопустимо");
				continue;
			}
			textcolor(YELLOW);
			gotoxy((wnd.X - 7) / 2, wherey() + 1);
			printf("Режим 2");
			mode_serial(func, x, n);
			break;
		}

	}

}
