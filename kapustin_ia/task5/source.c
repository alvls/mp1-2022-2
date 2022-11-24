#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>  
#include <locale.h>
#include <string.h>
#include<windows.h>
#include<omp.h>
//e:\\TEST\\*.*
void output_on_disp(int size, struct _finddata_t* arr, double t11)
{
    for (int i1 = 0; i1 < size; i1++)
        printf("Имя:%50s                 Размер(байт):%-20d\n", arr[i1].name, arr[i1].size);
    printf("---------------------------------------------------------------------------\n");
    printf("                       Время работы сортировки(msec) = %.10lf\n", t11);
}
double BubbleIncrease(struct _finddata_t* arr, long size)
{
    struct _finddata_t temp;
    double t1 = omp_get_wtime();
    for (int k = 0; k < size; k++)
    {
        for (int j = size - 1; j > k; j--)
        {
            if (arr[j - 1].size > arr[j].size)
            {
                temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
double BubbleDecrease(struct _finddata_t* arr, long size)
{
    double t1 = omp_get_wtime();
    struct _finddata_t temp;
    for (int k = 0; k < size; k++)
    {
        for (int j = size - 1; j > k; j--)
        {
            if (arr[j - 1].size < arr[j].size)
            {
                temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
double ChoiceSortIncrease(struct _finddata_t* arr, long size)
{
    double t1 = omp_get_wtime();
    struct _finddata_t temp;
    for (int i1 = 0; i1 < size - 1; i1++)
    {
        int minj = i1;
        for (int j = i1 + 1; j < size; j++)
            if (arr[j].size < arr[minj].size)
                minj = j;
        temp = arr[i1];
        arr[i1] = arr[minj];
        arr[minj] = temp;
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
double ChoiceSortDecrease(struct _finddata_t* arr, long size)
{
    double t1 = omp_get_wtime();
    struct _finddata_t temp;
    for (int i1 = 0; i1 < size - 1; i1++)
    {
        int minj = i1;
        for (int j = i1 + 1; j < size; j++)
            if (arr[j].size > arr[minj].size)
                minj = j;
        temp = arr[i1];
        arr[i1] = arr[minj];
        arr[minj] = temp;
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
double InsertionSortIncease(struct _finddata_t* arr, long size)
{
    double t1 = omp_get_wtime();
    struct _finddata_t temp;
    for (long i1 = 1; i1 < size; i1++)
    {
        int k = i1;
        while (k > 0 && arr[k - 1].size > arr[k].size)
        {
            temp = arr[k - 1];
            arr[k - 1] = arr[k];
            arr[k] = temp;
            k -= 1;
        }
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
double InsertionSortDecrease(struct _finddata_t* arr, long size)
{
    double t1 = omp_get_wtime();
    struct _finddata_t temp;
    for (long i1 = 1; i1 < size; i1++)
    {
        int k = i1;
        while (k > 0 && arr[k - 1].size < arr[k].size)
        {
            temp = arr[k - 1];
            arr[k - 1] = arr[k];
            arr[k] = temp;
            k -= 1;
        }
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
void mergeIncrease(struct _finddata_t* arr, long lb, long split, long ub)
{
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    struct _finddata_t* temp = malloc(sizeof(struct _finddata_t) * (ub - lb + 1));
    while (pos1 <= split && pos2 <= ub)
    {
        if (arr[pos1].size < arr[pos2].size)
            temp[pos3++] = arr[pos1++];
        else
            temp[pos3++] = arr[pos2++];
    }
    while (pos2 <= ub)
        temp[pos3++] = arr[pos2++];
    while (pos1 <= split)
        temp[pos3++] = arr[pos1++];
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        arr[lb + pos3] = temp[pos3];
    free(temp);
}
void mergeDecrease(struct _finddata_t* arr, long lb, long split, long ub)
{
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    struct _finddata_t* temp = malloc(sizeof(struct _finddata_t) * (ub - lb + 1));
    while (pos1 <= split && pos2 <= ub)
    {
        if (arr[pos1].size < arr[pos2].size)
            temp[pos3++] = arr[pos2++];
        else
            temp[pos3++] = arr[pos1++];
    }
    while (pos2 <= ub)
        temp[pos3++] = arr[pos2++];
    while (pos1 <= split)
        temp[pos3++] = arr[pos1++];
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        arr[lb + pos3] = temp[pos3];
    free(temp);
}
void SortMergeIncrease(struct _finddata_t* arr, long lb, long ub)
{
    long split;
    if (lb < ub)
    {
        split = (lb + ub) / 2;
        SortMergeIncrease(arr, lb, split);
        SortMergeIncrease(arr, split + 1, ub);
        mergeIncrease(arr, lb, split, ub);
    }

}
void SortMergeDecrease(struct _finddata_t* arr, long lb, long ub)
{
    long split;
    if (lb < ub)
    {
        split = (lb + ub) / 2;
        SortMergeDecrease(arr, lb, split);
        SortMergeDecrease(arr, split + 1, ub);
        mergeDecrease(arr, lb, split, ub);
    }

}
void QuickSortIncrease(struct _finddata_t* arr, long size_min, long size)
{
    if (size_min < size)
    {
        long i1 = size_min, j = size;
        struct _finddata_t temp, p;
        int med = (size_min + size) / 2;
        p = arr[med];
        do
        {
            while (arr[i1].size < p.size)
                i1++;
            while (arr[j].size > p.size)
                j--;

            if (i1 <= j)
            {
                temp = arr[i1];
                arr[i1] = arr[j];
                arr[j] = temp;
                i1++;
                j--;
            }

        } while (i1 <= j);
        QuickSortIncrease(arr, size_min, j);
        QuickSortIncrease(arr, i1, size);
    }
}

void QuickSortDecrease(struct _finddata_t* arr, long size_min, long size)
{
    if (size_min < size)
    {
        long i1 = size_min, j = size;
        struct _finddata_t temp, p;
        int med = (size_min + size) / 2;
        p = arr[med];
        do
        {
            while (arr[i1].size > p.size)
                i1++;
            while (arr[j].size < p.size)
                j--;

            if (i1 <= j)
            {
                temp = arr[i1];
                arr[i1] = arr[j];
                arr[j] = temp;
                i1++;
                j--;
            }

        } while (i1 <= j);
        QuickSortDecrease(arr, size_min, j);
        QuickSortDecrease(arr, i1, size);
    }
}
int incr(long inc[], long size)
{

    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do
    {
        if (++s % 2)
        {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;
}
double SortShellIncrease(struct _finddata_t* arr, long size)
{
    double t1 = omp_get_wtime();
    long inc, i, j, seq[40];
    int s;
    s = incr(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];

        for (i = inc; i < size; i++)
        {
            struct _finddata_t temp = arr[i];
            for (j = i - inc; (j >= 0) && (arr[j].size > temp.size); j -= inc)
                arr[j + inc] = arr[j];
            arr[j + inc] = temp;
        }
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
double SortShellDecrease(struct _finddata_t* arr, long size)
{
    double t1 = omp_get_wtime();
    long inc, i, j, seq[40];
    int s;
    s = incr(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];

        for (i = inc; i < size; i++)
        {
            struct _finddata_t temp = arr[i];
            for (j = i - inc; (j >= 0) && (arr[j].size < temp.size); j -= inc)
                arr[j + inc] = arr[j];
            arr[j + inc] = temp;
        }
    }
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
_fsize_t max_file_size(struct _finddata_t* arr, size_t lng)
{
    _fsize_t max = 0;
    for (int i1 = 0; i1 < lng; i1++)
    {
        if (arr[i1].size > max)
        {
            max = arr[i1].size;
        }
    }
    return max;
}
double countSortIncrease(struct _finddata_t* arr, size_t lng)
{
    double t1 = omp_get_wtime();
    int i1;
    _fsize_t m = max_file_size(arr, lng);
    _fsize_t* m1 = malloc(sizeof(int) * (m + 1));
    memset(m1, 0, sizeof(int) * (m + 1));
    for (i1 = 0; i1 < lng; i1++)
        m1[arr[i1].size]++;

    for (i1 = 1; i1 <= m; i1++)
        m1[i1] += m1[i1 - 1];
    struct _finddata_t* finalexit = malloc(sizeof(arr[0]) * lng);
    memset(finalexit, 0, sizeof(sizeof(arr[0])) * lng);
    for (i1 = lng - 1; i1 >= 0; i1--)
    {
        finalexit[m1[arr[i1].size] - 1] = arr[i1];
        m1[arr[i1].size]--;
    }

    for (i1 = 0; i1 < lng; i1++)
        arr[i1] = finalexit[i1];
    free(m1);
    free(finalexit);
    double t2 = omp_get_wtime();
    return(t2 - t1);
}
double countSortDecrease(struct _finddata_t* arr, size_t lng)
{
    double t1 = omp_get_wtime();
    int i1;
    _fsize_t m = max_file_size(arr, lng);
    _fsize_t* m1 = malloc(sizeof(int) * (m + 1));
    memset(m1, 0, sizeof(int) * (m + 1));
    for (i1 = 0; i1 < lng; i1++)
        m1[arr[i1].size]++;

    for (i1 = 1; i1 <= m; i1++)
        m1[i1] += m1[i1 - 1];
    struct _finddata_t* finalexit = malloc(sizeof(arr[0]) * lng);
    memset(finalexit, 0, sizeof(sizeof(arr[0])) * lng);
    for (i1 = lng - 1; i1 >= 0; i1--)
    {
        finalexit[m1[arr[i1].size] - 1] = arr[i1];
        m1[arr[i1].size--];
    }

    for (i1 = lng - 1; i1 >= 0; i1--)
        arr[i1] = finalexit[lng - 1 - i1];
    free(m1);
    free(finalexit);
    double t2 = omp_get_wtime();
    return(t2 - t1);
}

struct _finddata_t* main_arr;
struct _finddata_t* copy_arr;
double f;
void main(void)
{
    struct _finddata_t c_file;
    setlocale(LC_ALL, "RUS");
    intptr_t hFile;
    char way[200];
    int i = 0, cnt = 0;
    int temp, maxsize;
    int choice, choice1, n;
    double t1, t2;
    do
    {
        n = 1;
        printf("Введите путь к директории\n");
        fgets(way, 200, stdin);
        way[strlen(way) - 1] = '\0';

        if ((hFile = _findfirst(&way, &c_file)) == -1L)
        {
            printf("No files in current directory!\n");
            printf("Try again!\n");
            n = 0;
        }

    } while (n == 0);
    do
    {
        if (c_file.size > 0)
        {
            i++;
            printf("Имя: %50s      Размер: %-20d\n", c_file.name, c_file.size);
        }
    } while (_findnext(hFile, &c_file) == 0);
    printf("\ncount of files: %d\n", i);
    main_arr = calloc(i, sizeof(struct _finddata_t));
    hFile = _findfirst(way, &c_file);
    do
    {
        if (c_file.size > 0)
        {
            main_arr[cnt] = c_file;
            cnt++;
        }
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
    do
    {
        copy_arr = calloc(i, sizeof(struct _finddata_t));
        for (long l = 0; l < i; l++)
        {
            copy_arr[l] = main_arr[l];
        }
        n = 1;
        t1 = 0;
        t2 = 0;
        printf("\n\n\n\nВыберите  метод сортировки и введите его номер\n");
        printf("1 - Пузырьком \n");
        printf("2 - Выбором \n");
        printf("3 - Вставками \n");
        printf("4 - Слиянием \n");
        printf("5 - Хоара\n");
        printf("6 - Шелла \n");
        printf("7 - Подсчтетом\n");
        printf("0 - exit\n");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("1 - По возростанию \n");
            printf("2 - По убыванию \n");
            scanf_s("%d", &choice1);
            switch (choice1)
            {
            case 1:
                f = BubbleIncrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            case 2:
                f = BubbleDecrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            }
            break;
        case 2:
            printf("1 - По возростанию \n");
            printf("2 - По убыванию \n");
            scanf_s("%d", &choice1);
            switch (choice1)
            {
            case 1:
                f = ChoiceSortIncrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            case 2:
                f = ChoiceSortDecrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            }
            break;
        case 3:
            printf("1 - По возростанию \n");
            printf("2 - По убыванию \n");
            scanf("%d", &choice1);
            switch (choice1)
            {
            case 1:
                f = InsertionSortIncease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            case 2:
                f = InsertionSortDecrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            }break;
        case 4:
            printf("1 - По возростанию \n");
            printf("2 - По убыванию \n");
            scanf("%d", &choice1);
            switch (choice1)
            {
            case 1:
                t1 = omp_get_wtime();
                SortMergeIncrease(copy_arr, 0, i - 1);
                t2 = omp_get_wtime();
                output_on_disp(i, copy_arr, t2 - t1);
                n = 0;
                break;
            case 2:
                t1 = omp_get_wtime();
                SortMergeDecrease(copy_arr, 0, i - 1);
                t2 = omp_get_wtime();
                output_on_disp(i, copy_arr, t2 - t1);
                n = 0;
                break;
            }
            break;

        case 5:
            printf("1 - По возростанию \n");
            printf("2 - По убыванию \n");
            scanf("%d", &choice1);
            switch (choice1)
            {
            case 1:
                t1 = omp_get_wtime();
                QuickSortIncrease(copy_arr, 0, i - 1);
                t2 = omp_get_wtime();
                output_on_disp(i, copy_arr, t2 - t1);
                n = 0;
                break;
            case 2:
                t1 = omp_get_wtime();
                QuickSortDecrease(copy_arr, 0, i - 1);
                t2 = omp_get_wtime();
                output_on_disp(i, copy_arr, t2 - t1);
                n = 0;
                break;
            }
            break;
        case 6:
            printf("1 - По возростанию \n");
            printf("2 - По убыванию \n");
            scanf("%d", &choice1);
            switch (choice1)
            {
            case 1:
                f = SortShellIncrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            case 2:
                f = SortShellDecrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                n = 0;
                break;
            }
            break;
        case 7:
            printf("1 - По возростанию \n");
            printf("2 - По убыванию \n");
            scanf("%d", &choice1);
            switch (choice1)
            {
            case 1:
                f = countSortIncrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                maxsize = max_file_size(copy_arr, i);
                n = 0;
                break;
            case 2:
                f = countSortDecrease(copy_arr, i);
                output_on_disp(i, copy_arr, f);
                maxsize = max_file_size(copy_arr, i);
                n = 0;
                break;
            }
            break;
        case 0:
            break;
        default:
            printf("Неверное значение n, попробуйте снова\n");
            n = 0;
            break;
        }
    } while (n == 0);
}