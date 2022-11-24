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

#define MAX_MENU_ROW AVAILABLE_SORT_METHODS

COORD wnd;
int yTarget;

enum KEYCODES {
    NUMLOCK = -32,
    ENTER = 13,
    UP = 72,
    RIGHT = 75,
    LEFT = 77,
    DOWN = 80
};
enum COLUMNS {
    ALGORITHMS = 0,
    ORDERS = 1
};

char last_path[_MAX_PATH + 1] = "\0";
int last_sort_id = 0, last_order_id = 0;

int focus_col = 0;

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

int enumerate_dir(const char* path, int sort_id, int is_descending)
{
    struct _finddata_t c_file;
    intptr_t hFile;

    char search[MAX_PATH_FILTER + 1];
    strcpy_s(search, sizeof(search), path);
    strcat_s(search, sizeof(search), FILTER_ALL);
    search[MAX_PATH_FILTER] = '\0';

    if ((hFile = _findfirst(search, &c_file)) == -1L)
    {
        last_path[0] = '\0';
        textcolor(LIGHTMAGENTA);
        gotoxy(wnd.X / 2 - 16 / 2, wherey() + 1);
        printf("Каталог пуст :(");
        return 0;
    }

    size_t count = 0, subdir_count = 0;

    size_t bufsize = INITIAL_BUFFER_SIZE;
    struct _finddata_t* arr = malloc(sizeof(struct _finddata_t) * bufsize);
    struct _finddata_t* newarr;

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
                return 0;
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
        free(arr);
        return 0;
    }
    for (i = 0; i < count; i++)
    {
        iarr[i] = i;
    }

    double t_begin = omp_get_wtime();
    sort_methods[sort_id].func(arr, iarr, count, !is_descending);
    double t_end = omp_get_wtime();

    double time = t_end - t_begin;

    for (i = 0; i < count; i++)
    {
        print_file(arr[iarr[i]], 0);
    }

    textcolor(WHITE);
    gotoxy(wnd.X / 2 - (13 + strlen(sort_methods[sort_id].name)) / 2, wherey() + 2);
    printf("Сортировка: %s", sort_methods[sort_id].name);
    gotoxy(wnd.X / 2 - (8 + strlen(sort_orders[is_descending])) / 2, wherey() + 1);
    printf("Метод: %s", sort_orders[is_descending]);
    gotoxy(wnd.X / 2 - 12 / 2, wherey() + 1);
    printf("Каталоги : %d", subdir_count);
    gotoxy(wnd.X / 2 - 9 / 2, wherey() + 1);
    printf("Файлы : %d", count);

    textcolor(YELLOW);
    gotoxy(wnd.X / 2 - 16 / 2, wherey() + 2);
    printf("%.8lf сек.", time);

    free(arr);
    free(iarr);

    return 1;
}

void print_input_error(const char* text)
{
    textcolor(RED);
    gotoxy(wnd.X / 2 - strlen(text) / 2, wherey() + 1);
    printf(text);
    gotoxy(0, wherey() + 2);
    textcolor(LIGHTGRAY);
}

void print_option(int x, int is_selected, int is_focused, const char* text)
{
    gotoxy(x, wherey() + 1);
    textcolor(YELLOW);
    printf(" [%c] ", is_selected ? '+' : ' ');
    if (!is_selected || !is_focused)
    {
        textcolor(LIGHTGREEN);
    }
    printf("%s", text);
}

void print_header()
{
    hidecursor();

    gotoxy(0, 0);

    textcolor(CYAN);
    gotoxy(wnd.X / 2 - 28 / 2, wherey() + 1);
    printf("===========================");
    gotoxy(wnd.X / 2 - 28 / 2, wherey() + 1);
    printf("     Файловый менеджер     ");
    gotoxy(wnd.X / 2 - 28 / 2, wherey() + 1);
    printf("===========================");
    gotoxy(0, wherey() + 1);

    int i, yBegin = wherey() + 1;

    gotoxy(wnd.X / 2 + 28, yBegin);
    textcolor(GREEN);
    printf("Методы сортировки:");
    for (i = 0; i < AVAILABLE_SORT_ORDERS; i++)
    {
        print_option(wnd.X / 2 + 28, i == last_order_id, focus_col == ORDERS, sort_orders[i]);
    }

    gotoxy(wnd.X / 6 - 28 / 2, yBegin);
    textcolor(GREEN);
    printf("Алгоритмы сортировки:");
    for (i = 0; i < AVAILABLE_SORT_METHODS; i++)
    {
        print_option(wnd.X / 6 - 28 / 2, i == last_sort_id, focus_col == ALGORITHMS, sort_methods[i].name);
    }

    gotoxy(0, wherey() + 2);
    textcolor(LIGHTGRAY);

    showcursor();
}

void main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    clrscr();

    SMALL_RECT rect;
    getwindow(&rect, &wnd);

    print_header();
    yTarget = wherey();

    char path[_MAX_PATH + 1], buf[_MAX_PATH + 1];
    size_t path_len;

    int row = 0, delta_x;
    char ch = 0;

    while (1)
    {
        textcolor(LIGHTCYAN);
        gotoxy(wnd.X / 2 - 66 / 2, yTarget + 1);
        printf("Выберите параметры сортировки с помощью стрелочек и нажмите ENTER");

        while (ch != ENTER)
        {
            ch = getch();
            if (ch == NUMLOCK)
            {
                ch = _getch();
            }

            delta_x = 0;

            switch (ch)
            {
            case UP:
                delta_x = -1;
                break;
            case DOWN:
                delta_x = 1;
                break;
            case LEFT:
            case RIGHT:
                focus_col = (focus_col + 1) % 2;
                if (focus_col == ORDERS)
                {
                    row = last_order_id;
                }
                else
                {
                    row = last_sort_id;
                }
                break;
            }

            if (delta_x != 0)
            {
                row += delta_x;
                if (row < 0)
                {
                    row = MAX_MENU_ROW - 1;
                }
                else if (row >= MAX_MENU_ROW)
                {
                    row = 0;
                }
                if (focus_col == ORDERS)
                {
                    last_order_id = row % AVAILABLE_SORT_ORDERS;
                }
                else
                {
                    last_sort_id = row % AVAILABLE_SORT_METHODS;
                }
            }

            print_header();
        }

        gotoxy(wnd.X / 2 - 66 / 2, yTarget + 1);
        printf("%66c", ' ');

        textcolor(LIGHTCYAN);
        gotoxy(wnd.X / 2 - 39 / 2, wherey());
        printf("Введите путь к каталогу для сортировки");
        if (has_last_data())
        {
            gotoxy(wnd.X / 2 - 56 / 2, wherey() + 1);
            printf("(Если вы не хотите изменять путь, оставьте поле пустым)");
        }

        gotoxy(0, wherey() + 1);
        textcolor(LIGHTGRAY);

        gets_s(path, sizeof(path));
        path_len = strlen(path);
        if (path_len == 0 && !has_last_data())
        {
            print_input_error("Пожалуйста, введите начальный путь");
            continue;
        }

        clrscr();
        print_header();

        if (path_len > 2 && path[1] != ':')
        {
            strcpy_s(buf, sizeof(buf), last_path);
            strcat_s(buf, sizeof(buf), "\\");
            strcat_s(buf, sizeof(buf), path);
            buf[_MAX_PATH] = '\0';

            strcpy_s(last_path, sizeof(last_path), buf);
        }
        else if (path_len > 0)
        {
            strcpy_s(last_path, sizeof(last_path), path);
        }

        enumerate_dir(last_path, last_sort_id, last_order_id);
        yTarget = wherey() + 1;

        ch = 0;

        gotoxy(0, wherey() + 1);
    }
}