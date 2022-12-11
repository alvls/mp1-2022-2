#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "console_utils.h"

#include "math_functions.h"
#include "math_functions_list.h"
#include "calc_modes.h"

COORD wnd;
int yTarget;

void print_header()
{
    gotoxy(0, 0);

    textcolor(CYAN);
    gotoxy((wnd.X - 29) / 2, wherey() + 1);
    printf("===========================");
    gotoxy((wnd.X - 25) / 2, wherey() + 1);
    printf("     Аппроксиматор     ");
    gotoxy((wnd.X - 29) / 2, wherey() + 1);
    printf("===========================");

    textcolor(GREEN);
    gotoxy((wnd.X - 26) / 2, wherey() + 2);
    printf("Список доступных функций:");

    textcolor(LIGHTGREEN);
    gotoxy(4, wherey() + 1);
    for (int i = 0; i < AVAILABLE_MATH_FUNCTIONS; i++)
    {
        if (i == (AVAILABLE_MATH_FUNCTIONS / 2) + 1)
            gotoxy(4 + 2, wherey() + 1);
        printf("%s ", math_functions[i].name);

    }
    textcolor(LIGHTGRAY);
    gotoxy(0, wherey() + 2);
}

void print_help()
{
    textcolor(LIGHTBLUE);
    gotoxy((wnd.X - 110) / 2, wherey() + 1);
    printf("Для однократного расчета введите функцию, максимальное количество слагаемых (%d-%d) и точность (>= %lf)", N_MIN, N_MAX, MIN_PRECISION);
    gotoxy((wnd.X - 89) / 2, wherey() + 1);
    printf("Для работы в режиме серийного эксперимента введите функцию и количество слагаемых (%d-%d)", NMAX_MIN, NMAX_MAX);
    
    textcolor(LIGHTCYAN);
    gotoxy((wnd.X - 30) / 2, wherey() + 1);
    printf("Пример ввода функции: sin(0,5)");

    textcolor(LIGHTGRAY);
    gotoxy(0, wherey() + 2);
}
int extract_function_argument(const char* buf, double* x)
{
    char* arg_begin = strstr(buf, "(");
    if (!arg_begin)
    {
        return 0;
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
    for (int i = 0; i<AVAILABLE_MATH_FUNCTIONS; i++)
    {
        if (strcmp(math_functions[i].name, name) == 0)
            return &math_functions[i];
    }

    return 0;
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

    SMALL_RECT rect;
    getwindow(&rect, &wnd);

    char buf[128];
    int read;

    char func_input[16];
    double x, precision;
    int n;

    MathFunctionInfo* func = find_function(func_input);
    gotoxy(2, wherey());
    print_header();

    while (1)
    {
        print_help();

        printf("Введите вызов функции: ");
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

        if ((n > 1000) || (n < 1))
        {
            print_error("Введённое количество слагаемых не соответствует условию");
            continue;
        } 


        clrscr();
        print_header();

        textcolor(LIGHTMAGENTA);
        gotoxy((wnd.X - 36) / 2, wherey() + 1);
        printf("Расчёт функции %s(x), x = %lf\n", func->name, x);
        textcolor(LIGHTGRAY);

        switch (read)
        {
        case 3:
            if (precision < 0.000001)
            {
                print_error("Введённая точность не соответствует условию");
                continue;
            }
            textcolor(YELLOW);
            gotoxy((wnd.X - 7) / 2, wherey() + 1);
            printf("Режим 1");
            mode_single(func, x, n, precision);
            break;
        case 2:
            textcolor(YELLOW);
            gotoxy((wnd.X - 7) / 2, wherey() + 1);
            printf("Режим 2");
            mode_serial(func, x, n);
            break;
        }
        
    }
    
}
