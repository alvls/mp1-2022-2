#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <locale.h>

#include "console_utils.h"
#include "sort_methods.h"
#include "sort_orders.h"
#include "omp.h"

#define FILTER_ALL "\\*.*"
#define MAX_PATH_FILTER _MAX_PATH + (sizeof(FILTER_ALL) / sizeof(char)) - 1

#define INITIAL_BUFFER_SIZE 8

COORD wnd;

char last_path[_MAX_PATH + 1] = "\0";
int last_sort_id, last_order_id;

int has_last_data()
{
    return last_path[0] != '\0';
}

void print_file(struct _finddata_t c_file, int is_dir)
{
    struct tm loctime;
    char timestr[20 + 1];

    localtime_s(&loctime, &c_file.time_write);
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", &loctime);

    gotoxy(wnd.X / 4, wherey() + 1);
    if (is_dir)
    {
        printf("%-25.25s   %-10s", c_file.name, timestr);
    }
    else
    {
        printf("%-25.25s   %-10s   %-20lu", c_file.name, timestr, c_file.size);
    }
}

void enumerate_dir(const char* path, int sort_id, int is_descending)
{
    struct _finddata_t c_file;
    intptr_t hFile;

    char search[MAX_PATH_FILTER + 1];
    strcpy_s(search, sizeof(search), path);
    strcat_s(search, sizeof(search), FILTER_ALL);
    search[MAX_PATH_FILTER - 1] = '\0';

    if ((hFile = _findfirst(search, &c_file)) == -1L)
    {
        last_path[0] = '\0';
        textcolor(LIGHTMAGENTA);
        gotoxy(wnd.X / 2 - 16 / 2, wherey() + 1);
        printf("Каталог пуст :(");
        return;
    }

    size_t count = 0, subdir_count = 0;

    size_t bufsize = INITIAL_BUFFER_SIZE;
    struct _finddata_t* arr = malloc(sizeof(struct _finddata_t) * bufsize);
    struct _finddata_t* newarr = malloc(sizeof(struct _finddata_t) * bufsize);

    if (!arr)
    {
        textcolor(RED);
        printf("Генерал Фейлор читает ваш диск :)\n");
        return;
    }

    textcolor(WHITE);
    gotoxy(wnd.X / 2 - (23 + strlen(path)) / 2, wherey() + 1);
    printf("Содержимое каталога '%s'", path);
    gotoxy(wnd.X / 4, wherey() + 2);
    printf("%-25.25s   %-20s  %-10s", "FILE", "DATE", "SIZE");
    gotoxy(wnd.X / 4, wherey() + 1);
    printf("%-25.25s   %-20s  %-10s", "----", "----", "----");

    textcolor(LIGHTGRAY);

    do {
        if (c_file.attrib & _A_SUBDIR)
        {
            subdir_count++;
            print_file(c_file, 1);
            continue;
        }

        if (count == bufsize)
        {
            bufsize *= 2;
            newarr = realloc(arr, sizeof(c_file) * bufsize);
            if (!arr)
            {
                textcolor(RED);
                printf("Недостаточно памяти :(\n");
                free(arr);
                return;
            }
            arr = newarr;
        }
        arr[count++] = c_file;
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);

    size_t i;

    size_t* iarr = malloc(count * sizeof(size_t));
    if (!iarr)
    {
        textcolor(RED);
        printf("Недостаточно памяти (iarr) :(\n");
        return;
    }
    for (i = 0; i < count; i++)
    {
        iarr[i] = i;
    }

    double t_begin = omp_get_wtime();
    sort_methods[sort_id].func(arr, iarr, count, !is_descending);
    double t_end = omp_get_wtime();

    double time = t_end- t_begin;

    for (i = 0; i < count; i++)
    {
        print_file(arr[iarr[i]], 0);
    }

    textcolor(WHITE);
    gotoxy(wnd.X / 2 - (13 + strlen(sort_methods[sort_id].name)) / 2, wherey() + 2);
    printf("Сортировка: %s", sort_methods[sort_id].name);
    gotoxy(wnd.X / 2 - (8 + strlen(sort_orders[is_descending])) / 2, wherey() + 1);
    printf("Метод: %s", sort_orders[is_descending]);
    gotoxy(wnd.X / 2 - 16 / 2, wherey() + 1);
    printf("Каталоги : %d", subdir_count);
    gotoxy(wnd.X / 2 - 10 / 2, wherey() + 1);
    printf("Файлы : %d", count);

    textcolor(YELLOW);
    gotoxy(wnd.X / 2 - 16 / 2, wherey() + 1);
    printf("%.8lf сек.", time);

    free(arr);
    free(iarr);
}

void print_input_error(const char* text)
{
    textcolor(RED);
    gotoxy(wnd.X / 2 - strlen(text) / 2, wherey() + 1);
    printf(text);
    gotoxy(0, wherey() + 2);
    textcolor(LIGHTGRAY);
}

void print_option(int x, int id, const char* prefix, const char* text)
{
    gotoxy(x, wherey() + 1);
    textcolor(YELLOW);
    printf(" %s[%d] ", prefix, id);
    textcolor(LIGHTGREEN);
    printf("%s", text);
}

void print_header()
{
    gotoxy(0, 0);

    textcolor(CYAN);
    gotoxy(wnd.X / 2 - 28 / 2, wherey() + 1);
    printf("===========================");
    gotoxy(wnd.X / 2 - 28 / 2, wherey() + 1);
    printf("     Файловый менеджер     ");
    gotoxy(wnd.X / 2 - 28 / 2, wherey() + 1);
    printf("===========================");
    gotoxy(0, wherey() + 1);

    int i, baseY = wherey();

    gotoxy(wnd.X / 2 + 28, baseY + 1);
    textcolor(GREEN);
    printf("Методы сортировки:");
    if (has_last_data())
    {
        print_option(wnd.X / 2 + 28, 0, " ", sort_orders[last_order_id]);
    }
    for (i = 0; i < AVAILABLE_SORT_ORDERS; i++)
    {
        print_option(wnd.X / 2 + 28, i + 1, " ", sort_orders[i]);
    }

    gotoxy(wnd.X / 6 - 28 / 2, baseY + 1);
    textcolor(GREEN);
    printf("Алгоритмы сортировки:");
    if (has_last_data())
    {
        print_option(wnd.X / 6 - 28 / 2, 0, " ", sort_methods[last_sort_id].name, " ");
    }
    for (i = 0; i < AVAILABLE_SORT_METHODS; i++)
    {
        print_option(wnd.X / 6 - 28 / 2, i + 1, " ", sort_methods[i].name, " ");
    }

    gotoxy(0, wherey() + 2);
    textcolor(LIGHTGRAY);
}

void handle_command(int sort_id, int order_id, const char* path)
{
    if (sort_id < 0 || sort_id - 1 > AVAILABLE_SORT_METHODS)
    {
        print_input_error("Введён некорректный номер алгоритма сортировки");
        return;
    }
    if (order_id < 0 || order_id - 1 > AVAILABLE_SORT_ORDERS)
    {
        print_input_error("Введён некорректный номер метода сортировки");
        return;
    }

    if (!path)
    {
        path = last_path;
    }
    else
    {
        if (strlen(path) > 2 && path[1] != ':')
        {
            char buf[_MAX_PATH + 1];
            strcpy_s(buf, sizeof(buf), last_path);
            strcat_s(buf, sizeof(buf), "\\");
            strcat_s(buf, sizeof(buf), path);
            buf[_MAX_PATH - 1] = '\0';

            path = buf;
        }

        strcpy_s(last_path, sizeof(last_path), path);
    }

    if (sort_id == 0)
        sort_id = last_sort_id;
    else
        last_sort_id = --sort_id;

    if (order_id == 0)
        order_id = last_order_id;
    else
        last_order_id = --order_id;

    clrscr();
    print_header();

    enumerate_dir(path, sort_id, order_id);
}

void main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    clrscr();

    SMALL_RECT rect;
    getwindow(&rect, &wnd);

    print_header();

    char input[_MAX_PATH + 4 + 1];
    int sort_id, order_id;
    char path[_MAX_PATH + 1];
    int read;

    while (1)
    {
        textcolor(LIGHTCYAN);
        gotoxy(wnd.X / 2 - 69 / 2, wherey() + 1);
        printf("Введите через пробел номер алгоритма сортировки, номер метода и путь");
        if (has_last_data())
        {
            gotoxy(wnd.X / 2 - 83 / 2, wherey() + 1);
            printf("(Если вы не хотите изменять метод сортировки или путь, оставьте эти поля пустыми)");
        }
        gotoxy(0, wherey() + 1);
        textcolor(LIGHTGRAY);

        gets_s(input, sizeof(input));

        read = sscanf_s(input, "%d %d %[^\n]", &sort_id, &order_id, &path, sizeof(path));
        if (read < 3 && !has_last_data())
        {
            print_input_error("Пожалуйста, введите начальные параметры сортировки и путь");
            continue;
        }

        switch (read)
        {
        case 1:
            handle_command(sort_id, 0, 0);
            break;
        case 2:
            handle_command(sort_id, order_id, 0);
            break;
        case 3:
            handle_command(sort_id, order_id, path);
            break;
        }

        gotoxy(0, wherey() + 1);
    }
}