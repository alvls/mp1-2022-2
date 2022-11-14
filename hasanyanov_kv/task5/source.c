#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>
#include <locale.h>
#include "C.h"
#include "Windows.h"

#define ESCAPE 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define SPACE 32
#define DEL 8
#define SIZE_MENU 9

void bubbleSort(struct _finddata_t* a, size_t size) // Сортировка пузырьком
{
    long i, j;
    struct _finddata_t x;
    for (i = 0; i < size; i++)
    {
        for (j = size - 1; j > i; j--)
        {
            if (a[j - 1].size > a[j].size)
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
    }
}
void selectSort(struct _finddata_t* a, long size) // Сортировка выбором
{
    long i, j, k;
    struct _finddata_t x;

    for (i = 0; i < size; i++)
    {
        k = i; x = a[i];

        for (j = i + 1; j < size; j++)
            if (a[j].size < x.size)
            {
                k = j; x = a[j];
            }

        a[k] = a[i]; a[i] = x;
    }
}
void insertSort(struct _finddata_t* a, long size) // Сортировка вставками
{
    struct _finddata_t x;
    long i, j;

    for (i = 0; i < size; i++)
    {
        x = a[i];
        for (j = i - 1; j >= 0 && a[j].size > x.size; j--)
            a[j + 1] = a[j];
        a[j + 1] = x;
    }
}
void merge(struct _finddata_t* a, long lb, long split, long ub)
{
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    struct _finddata_t* temp = malloc(sizeof(struct _finddata_t) * (ub - lb + 1));
    while (pos1 <= split && pos2 <= ub)
    {
        if (a[pos1].size < a[pos2].size)
            temp[pos3++] = a[pos1++];
        else
            temp[pos3++] = a[pos2++];
    }
    while (pos2 <= ub)
        temp[pos3++] = a[pos2++];
    while (pos1 <= split)
        temp[pos3++] = a[pos1++];
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        a[lb + pos3] = temp[pos3];

    free(temp);
}
void mergeSort(struct _finddata_t* a[], long lb, long ub)
{
    long split;

    if (lb < ub)
    {

        split = (lb + ub) / 2;

        mergeSort(a, lb, split);
        mergeSort(a, split + 1, ub);
        merge(a, lb, split, ub);
    }
}
void quickSort(struct _finddata_t* a, long N) // Сортировка Хоара (быстрая)
{
    long i = 0, j = N - 1;
    struct _finddata_t temp, p;

    p = a[N >> 1];
    do {
        while (a[i].size < p.size)
            i++;
        while (a[j].size > p.size)
            j--;

        if (i <= j)
        {
            temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0)
        quickSort(a, j);
    if (N > i)
        quickSort(a + i, N - i);
}
int increment(long inc[], long size)
{
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2)
        {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else
        {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);
    return s > 0 ? --s : 0;
}
void shellSort(struct _finddata_t* a, long size)
{
    long inc, i, j, seq[40];
    int s;
    s = increment(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];

        for (i = inc; i < size; i++)
        {
            struct _finddata_t temp = a[i];
            for (j = i - inc; (j >= 0) && (a[j].size > temp.size); j -= inc)
                a[j + inc] = a[j];
            a[j + inc] = temp;
        }
    }
}
_fsize_t max_file_size(struct _finddata_t* arr, size_t len)
{
    _fsize_t max = 0;

    for (int i = 0; i < len; i++)
    {
        if (arr[i].size > max)
        {
            max = arr[i].size;
        }
    }

    return max;
}
void countingSort(struct _finddata_t* arr, size_t len)
{
    int i, j;
    _fsize_t k = max_file_size(arr, len);

    _fsize_t* cnt = malloc(sizeof(int) * (k + 1));
    memset(cnt, 0, sizeof(int) * (k + 1));

    for (i = 0; i < len; i++)
    {
        cnt[arr[i].size]++;
    }

    for (i = 1; i <= k; i++)
    {
        cnt[i] += cnt[i - 1];
    }

    struct _finddata_t* res = malloc(sizeof(arr[0]) * len);
    memset(res, 0, sizeof(sizeof(arr[0])) * len);

    for (i = len - 1; i >= 0; i--)
    {
        res[cnt[arr[i].size] - 1] = arr[i];
        cnt[arr[i].size]--;
    }

    for (i = 0; i < len; i++)
    {
        arr[i] = res[i];
    }

    free(cnt);
    free(res);
}
void directive(char* path, int sort, int variant_sort) // Введем функцию, которая будет заполнять массив характеристиками файлов, сортировать его и выводить на экран.
{
    struct _finddata_t c_file;
    struct _finddata_t* c_file_buf;
    intptr_t hFile;

    char timebuf[21], target[200 + 4];
    struct tm timeinfo;
    int count = 0;
    clock_t end, start;

    strcpy(target, path);
    strcat(target, "\\*.*");

    if ((hFile = _findfirst(target, &c_file)) == -1L)
        printf("В выбранном каталоге отсутствуют файлы\n");
    else
    {
        int bufsize = 8; // Изначально возьмём память для 8 файлов, в будущем будем ее увеличивать вдвое при необходимости.

        c_file_buf = malloc(sizeof(c_file) * bufsize);

        char buffer[30];


        ctime_s(buffer, _countof(buffer), &c_file.time_write);
        if (!c_file_buf)
        {
            printf("Память закончилась :(");
            return;
        }
        do
        {
            if (count == bufsize)
            {
                bufsize *= 2;
                c_file_buf = realloc(c_file_buf, sizeof(c_file) * bufsize);
                if (!c_file_buf)
                {
                    printf("Память закончилась :(");
                    return;
                }
            }
            c_file_buf[count] = c_file;
            count++;
        } while (_findnext(hFile, &c_file) == 0);
        printf("\nИмя файла:                        Дата: %13c  Размер:|\n", ' ');
        printf("---------------------------------------------------------------\n");
        _findclose(hFile);

        start = clock();
        switch (sort)
        {
        case 0:
        {
            bubbleSort(c_file_buf, count);
            break;
        }
        case 1:
        {
            selectSort(c_file_buf, count);
            break;
        }
        case 2:
        {
            insertSort(c_file_buf, count);
            break;
        }
        case 3:
        {
            mergeSort(c_file_buf, 0, count - 1);
            break;
        }
        case 4:
        {
            quickSort(c_file_buf, count);
            break;
        }
        case 5:
        {
            shellSort(c_file_buf, count);
            break;
        }
        case 6:
        {
            countingSort(c_file_buf, count);
            break;
        }
        
        }
        end = clock();
        if (variant_sort == 0)
        {
            for (int i = 0; i < count; i++)
            {
                c_file = c_file_buf[i];
                localtime_s(&timeinfo, &c_file.time_write);
                strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", &timeinfo);
                printf("%-25.25s    %-10s  %-20lu\n", c_file.name, timebuf, c_file.size);

            }
        }
        else if (variant_sort == 1)
        {
            for (int i = count - 1; i >= 0; i--)
            {
                c_file = c_file_buf[i];
                localtime_s(&timeinfo, &c_file.time_write);
                strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", &timeinfo);
                printf("%-25.25s    %-10s  %-20lu\n", c_file.name, timebuf, c_file.size);

            }
        }
        printf("\nКоличество файлов: %lu\n", count);
        printf("Время сортировки: %ldms\n", (end - start));
    }
}

void main()
{
    system("title Сортировщик файлов");
    setlocale(LC_ALL, "Russian");
    textcolor(GREEN);
    int mode1, mode2;
    char path[200 + 1];
    char menu[SIZE_MENU][30] = { "Сортировка пузырьком", "Сортировка выбором", "Сортировка вставками", "Сортровка слиянием", "Сортировка 'Хоара'", "Сортировка 'Шелла'", "Сортировка подсчётом", "Выбрать новую папку", "Выход" };
    char menu2[2][30] = { "Сортировать по возрастанию", "Сортировать по убыванию" };
    int active_menu;
    char ch;
    char ch2;
    int active_menu2;
    int flag;

    while (1)
    {
        mode1 = 1; mode2 = 2; active_menu = 0; active_menu2 = 0;
        printf("Введите путь к нужной папке:\n");
        scanf_s("%s", path, sizeof(path));

        while (1)
        {
            clrscr();
            hidecursor();
            gotoxy(0, 0);
            textcolor(LIGHTGREEN);
            printf("Выберите способ сортировки:\n");
            for (long i = 0; i < SIZE_MENU; i++)
            {
                if (i == active_menu)
                    textcolor(LIGHTGREEN);
                else
                    textcolor(LIGHTGRAY);
                gotoxy(1, i + 1);
                printf("* %s *", menu[i]);
            }

            ch = _getch();
            if (ch == -32)
                ch = _getch();
            switch (ch)
            {
            case UP:
                if (active_menu > 0)
                    --active_menu;
                break;
            case DOWN:
                if (active_menu < SIZE_MENU - 1)
                    ++active_menu;
                break;
            case ESCAPE:
                exit(0);
                break;
            case ENTER:
                clrscr();
                textcolor(GREEN);
                flag = 1;
                switch (active_menu)
                {
                case 7:
                    mode1 = 0;
                    break;
                case 8:
                    exit(0);
                    break;
                }
                if (mode1 == 0)
                    break;
                while (flag)
                {
                    
                    for (long i = 0; i < 2; i++)
                    {
                        if (i == active_menu2)
                            textcolor(LIGHTGREEN);
                        else
                            textcolor(LIGHTGRAY);
                        gotoxy(1, i + 1);
                        printf("* %s *", menu2[i]);
                    }
                    textcolor(GREEN);
                    ch2 = _getch();
                    if (ch2 == -32)
                        ch2 = _getch();
                    switch (ch2)
                    {
                    case UP:
                        if (active_menu2 > 0)
                            --active_menu2;
                        break;
                    case DOWN:
                        if (active_menu2 < 1)
                            ++active_menu2;
                        break;
                    case ESCAPE:
                        exit(0);
                        break;
                    case ENTER:
                        
                        flag = 0;
                        break;
                    }
                }

                clrscr();
                directive(path, active_menu, active_menu2);
                system("PAUSE");
                break;
            }
            if (mode1 == 0)
                break;
        }
    }
}
