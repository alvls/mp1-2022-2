#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
#include <io.h>
#include <memory.h>
#include <time.h>
#include "omp.h"
#include <locale.h>


void BubbleSort(struct _finddata_t* a, size_t size)
{
    long i, j;
    struct _finddata_t temp;
    for (i = 0; i < size; i++)
    {
        for (j = size - 1; j > i; j--)
        {
            if (a[j - 1].size > a[j].size)
            {
                temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;
            }
        }
    }
}
void SelectSort(struct _finddata_t* a, long size)
{
    long i, j, k;
    struct _finddata_t temp;

    for (i = 0; i < size; i++)
    {
        k = i; temp = a[i];

        for (j = i + 1; j < size; j++)
            if (a[j].size < temp.size)
            {
                k = j; temp = a[j];
            }

        a[k] = a[i]; a[i] = temp;
    }
}
void InsertSort(struct _finddata_t* a, long size)
{
    struct _finddata_t temp;
    long i, j;

    for (i = 0; i < size; i++)
    {
        temp = a[i];
        for (j = i - 1; j >= 0 && a[j].size > temp.size; j--)
            a[j + 1] = a[j];
        a[j + 1] = temp;
    }
}
void Merge(struct _finddata_t* a, long lb, long split, long ub)
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
void MergeSort(struct _finddata_t* a[], long lb, long ub)
{
    long split;

    if (lb < ub)
    {

        split = (lb + ub) / 2;

        MergeSort(a, lb, split);
        MergeSort(a, split + 1, ub);
        Merge(a, lb, split, ub);
    }
}
void HoareSort(struct _finddata_t* a, long N)
{
    long i = 0, j = N - 1;
    struct _finddata_t temp, q;

    q = a[N >> 1];
    do {
        while (a[i].size < q.size)
            i++;
        while (a[j].size > q.size)
            j--;

        if (i <= j)
        {
            temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0)
        HoareSort(a, j);
    if (N > i)
        HoareSort(a + i, N - i);
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
void ShellSort(struct _finddata_t* a, long size)
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
void CountingSort(struct _finddata_t* arr, size_t len)
{
    int i, j;
    _fsize_t k = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (arr[i].size > k)
        {
            k = arr[i].size;
        }
    }

    _fsize_t* count = malloc(sizeof(int) * (k + 1));
    if (!count)
    {
        printf("Недостаточно памяти!\n");
        return;
    }
    memset(count, 0, sizeof(int) * (k + 1));

    for (i = 0; i < len; i++)
    {
        count[arr[i].size]++;
    }

    for (i = 1; i <= k; i++)
    {
        count[i] += count[i - 1];
    }

    struct _finddata_t* out = malloc(sizeof(struct _finddata_t) * len);
    memset(out, 0, sizeof(sizeof(struct _finddata_t)) * len);

    for (i = len - 1; i >= 0; i--)
    {
        out[count[arr[i].size] - 1] = arr[i];
        count[arr[i].size]--;
    }

    for (i = 0; i < len; i++)
    {
        arr[i] = out[i];
    }

    free(count);
    free(out);
}

void print_file(struct _finddata_t c_file)
{
    char buffer[30];
    ctime_s(buffer, _countof(buffer), &c_file.time_write);
    printf("%-30.30s   %.24s  %10lu\n", c_file.name, buffer, c_file.size);
}

void list_dir(int sort_method, int sort_direction, char* path)
{
    char search[_MAX_PATH + 4 + 1];
    strcpy_s(search, sizeof(search), path);
    strcat_s(search, sizeof(search), "\\*.*");
    search[_MAX_PATH + 4] = '\0';

    intptr_t hFile;
    struct _finddata_t c_file;
    if ((hFile = _findfirst(search, &c_file)) == -1L)
    {
        printf("В каталоге отсутствуют файлы!\n");;
        return;
    }

    size_t count = 0;

    do {
        count++;
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);

    struct _finddata_t* arr = malloc(count * sizeof(struct _finddata_t));

    hFile = _findfirst(search, &c_file);
    for (size_t i = 0; i < count; i++)
    {
        _findnext(hFile, &c_file);
        arr[i] = c_file;
    }
    _findclose(hFile);

    double start_time = omp_get_wtime();

    switch (sort_method)
    {
    case 1:
        BubbleSort(arr, count);
        break;
    case 2:
        SelectSort(arr, count);
        break;
    case 3:
        InsertSort(arr, count);
        break;
    case 4:
        MergeSort(arr, 0, count - 1);
        break;
    case 5:
        HoareSort(arr, count);
        break;
    case 6:
        ShellSort(arr, count);
        break;
    case 7:
        CountingSort(arr, count);
        break;
    default:
        printf("Неизвестный алгоритм сортировки\n");
        free(arr);
        return;
    }

    double end_time = omp_get_wtime();

    if (sort_direction != 1 && sort_direction != 2)
    {
        printf("Неизвестное направление сортировки\n");
        return;;
    }
    textcolor(YELLOW);
    printf("Текущая директория: %s\n\n", path);
    textcolor(WHITE);
    printf("%-30.30s   %-25s  %-10s\n", "FILE", "DATE", "SIZE");
    printf("%-30.30s   %-25s  %-10s\n", "----", "----", "----");
    if (sort_direction == 1)
    {
        for (size_t i = 0; i < count; i++)
        {
            print_file(arr[i]);
        }
    }
    else
    {
        for (size_t i = count - 1; i-- > 0; )
        {
            print_file(arr[i]);
        }
    }
    printf("                                                                                                         ");
    textcolor(CYAN);
    printf("                                                      Время сортировки: %lf сек.\n", end_time - start_time);
    textcolor(WHITE);
    free(arr);
}


void main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "Russian");

    int last_sort_id = -1, last_sort_order = -1;
    char last_path[_MAX_PATH + 1] = "#";

    int sort_id, sort_order;
    char path[_MAX_PATH + 1];

    char c;

    clrscr();
    while (1)
    {
        printf("Введите путь (если вы уже выбирали путь и желаете остаться в этом каталоге, нажмите Enter): ");
        gets_s(path, sizeof(path));

        printf("\nСписок алгоритмов сортировки:\n");
        if (last_sort_id != -1)
        {
            printf(" 0 - Последний выбранный алгоритм\n");
        }
        printf(" 1 - Пузырьком\n");
        printf(" 2 - Выбором\n");
        printf(" 3 - Вставками\n");
        printf(" 4 - Слиянием\n");
        printf(" 5 - Хоара\n");
        printf(" 6 - Шелла\n");
        printf(" 7 - Подсчётом\n");
        printf("Выберите алгоритм сортировки: ");
        scanf_s("%d", &sort_id);

        printf("\nСписок методов сортировки:\n");
        if (last_sort_order != -1)
        {
            printf(" 0 - Последний выбранный метод\n");
        }
        printf(" 1 - По возрастанию\n");
        printf(" 2 - По убыванию\n");
        printf("Выберите метод сортировки: ");
        scanf_s("%d", &sort_order);

        if (sort_id == 0)
        {
            if (last_sort_id == -1)
            {
                printf("*** Пожалуйста, выберите начальный алгоритм сортировки\n");
                continue;
            }
            sort_id = last_sort_id;
        }
        if (sort_order == 0)
        {
            if (last_sort_order == -1)
            {
                printf("*** Пожалуйста, выберите начальный метод сортировки\n");
                continue;
            }
            sort_order = last_sort_order;
        }
        if (strlen(path) == 0)
        {
            if (last_path[0] == '#')
            {
                printf("*** Пожалуйста, выберите начальный каталог для сортировки\n");
                continue;
            }
        }
        else
        {
            strcpy_s(last_path, sizeof(last_path), path);
        }

        last_sort_id = sort_id;
        last_sort_order = sort_order;

        clrscr();
        list_dir(last_sort_id, last_sort_order, last_path);
        getchar();
    }
}
