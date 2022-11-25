#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>
#include <locale.h>
#include <string.h>
#include "omp.h"
struct _finddata_t c_file;
struct _finddata_t* files2;

short increase_or_decrease()
{
    short answer;
    printf("Файлы в директории нужно отсортировать по возрастанию или по убыванию размера? (Если по возрастанию, введите '1', по убыванию - '2')\t");
    scanf_s("%hi", &answer);
    while (getchar() != '\n');
    if ((answer != 1) && (answer != 2))
    {
        printf("Способ сортировки введен некорректно\n");
        return 3;
    }
    else return answer;
}

void print_of_table_increase(int size)
{
    printf("Имя           Размер\n", ' ');
    for (int i = 0; i < size; i++)
        printf("%-12.12s  %lld байт\n", files2[i].name, files2[i].size);
}

void print_of_table_decrease(int size)
{
    printf("Имя           Размер\n", ' ');
    for (int i = size - 1; i >= 0; i--)
        printf("%-12.12s  %lld байт\n", files2[i].name, files2[i].size);
}

void copy_arrays(struct _finddata_t arr[], int size)
{
    for (int i = 0; i < size; i++)
        files2[i] = arr[i];
}

void bubble_sort(int size)
{
    for (int i = 0; i < size; i++)
        for (int j = size - 1; j > i; j--)
            if (files2[j].size < files2[j - 1].size)
            {
                c_file = files2[j];
                files2[j] = files2[j - 1];
                files2[j - 1] = c_file;
            }
    return;
}

void select_sort(int size)
{
    int ind;
    for (int i = 0; i < size - 1; i++)
    {
        c_file = files2[i];
        ind = i;
        for (int j = i + 1; j < size; j++)
            if (files2[j].size < c_file.size)
            {
                c_file = files2[j];
                ind = j;
            }
        if (ind != i)
        {
            c_file = files2[ind];
            files2[ind] = files2[i];
            files2[i] = c_file;
        }
    }
    return;
}

void insert_sort(int size)
{
    int j;
    for (int i = 1; i < size; i++)
    {
        j = i - 1;
        c_file = files2[i];
        while ((files2[j].size > c_file.size) && (j > 0))
        {
            files2[j + 1] = files2[j];
            j--;
        }
        files2[j + 1] = c_file;
    }
    return;
}

void merge(int left, int middle, int right)
{
    struct _finddata_t* arr2 = (struct _finddata_t*)malloc((right - left + 1) * sizeof(struct _finddata_t));
    int k = 0, i = left, j = middle + 1;
    while (k < (right - left + 1))
    {
        while ((i <= middle) && (j <= right))
        {
            if (files2[i].size < files2[j].size)
            {
                arr2[k] = files2[i];
                i++;
            }
            else
            {
                arr2[k] = files2[j];
                j++;
            }
            k++;
        }
        if (i > middle)
            while (j <= right)
            {
                arr2[k] = files2[j];
                j++;
                k++;
            }
        else while (i <= middle)
        {
            arr2[k] = files2[i];
            i++;
            k++;
        }
    }
    for (i = left; i <= right; i++)
        files2[i] = arr2[i - left];
    free(arr2);
    return;
}

void merge_sort(int left, int right)
{
    int middle;
    if (left == right) return;
    if ((left + right) % 2 != 0) middle = (left + right) / 2;
    else middle = (left + right) / 2;
    merge_sort(left, middle);
    merge_sort(middle + 1, right);
    merge(left, middle, right);
    return;
}

void quick_sort(int left, int right)
{

    int left_limit = left, right_limit = right;
    struct _finddata_t point = files2[left];
    while (left < right)
    {
        while ((files2[right].size >= point.size) && (left < right))
            right--;
        if (left != right)
        {
            files2[left] = files2[right];
            left++;
        }
        while ((files2[left].size <= point.size) && (left < right))
            left++;
        if (left != right)
        {
            files2[right] = files2[left];
            right--;
        }
    }
    files2[left] = point;
    if (left_limit < left)
        quick_sort(left_limit, left - 1);
    if (left < right_limit)
        quick_sort(left + 1, right_limit);
}

void shell_sort(int size)

{
    int step = 4, j;
    struct _finddata_t tmp_i;
    while (step > 0)
    {
        for (int i = 0; i < size; i++)
        {
            j = i;
            tmp_i = files2[i];
            while ((j >= step) && (files2[j - step].size > tmp_i.size))
            {
                files2[j] = files2[j - step];
                j = j - step;
            }
            files2[j] = tmp_i;
        }
        if (step > 1) step /= 2;
        else step = 0;
    }
}

void counting_sort(int size)
{
    int* arr;
    int  i, ind = 0, k = 0, j;
    for (i = 0; i < size; i++)
        if (files2[i].size > files2[ind].size) ind = i;
    ind = files2[ind].size + 1;
    arr = (int*)malloc(ind * sizeof(int));
    memset(arr, 0, (ind * sizeof(int)));
    for (i = 0; i < size; i++)
        arr[files2[i].size]++;
    for (i = 0; i < ind; i++)
        while (arr[i] > 0)
        {
            j = k;
            while (i != files2[j].size) j++;
            c_file = files2[k];
            files2[k] = files2[j];
            files2[j] = c_file;
            k++;
            arr[i]--;
        }
    free(arr);
}
void radix_sort(int size)
{
    int count[10] = { 0 };
    int digit = 1;
    int ind, k = 0;
    struct _finddata_t* arr0 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr1 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr2 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr3 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr4 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr5 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr6 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr7 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr8 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    struct _finddata_t* arr9 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    do
    {
        k = 0;
        for (int i = 0; i < size; i++)
        {
            ind = (files2[i].size / digit) % 10;
            switch (ind)
            {
            case 0: arr0[count[0]] = files2[i];
                break;
            case 1: arr1[count[1]] = files2[i];
                break;
            case 2: arr2[count[2]] = files2[i];
                break;
            case 3: arr3[count[3]] = files2[i];
                break;
            case 4: arr4[count[4]] = files2[i];
                break;
            case 5: arr5[count[5]] = files2[i];
                break;
            case 6: arr6[count[6]] = files2[i];
                break;
            case 7: arr7[count[7]] = files2[i];
                break;
            case 8: arr8[count[8]] = files2[i];
                break;
            case 9: arr9[count[9]] = files2[i];
                break;
            }
            count[ind]++;
        }
        if (count[0] == size) ind = 0;
        //if ((arr1[0].size == 0) && (arr2[0].size == 0) && (arr3[0].size == 0) && (arr4[0].size == 0) && (arr5[0].size == 0) && (arr6[0].size == 0) && (arr7[0].size == 0) && (arr8[0].size == 0) && (arr9[0].size == 0)) ind = 0;
        else ind = 1;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < count[i]; j++)
            {
                switch (i)
                {
                case 0: files2[k] = arr0[j];
                    arr0[j].size = 0;
                    break;
                case 1: files2[k] = arr1[j];
                    arr1[j].size = 0;
                    break;
                case 2: files2[k] = arr2[j];
                    arr2[j].size = 0;
                    break;
                case 3: files2[k] = arr3[j];
                    arr3[j].size = 0;
                    break;
                case 4: files2[k] = arr4[j];
                    arr4[j].size = 0;
                    break;
                case 5: files2[k] = arr5[j];
                    arr5[j].size = 0;
                    break;
                case 6: files2[k] = arr6[j];
                    arr6[j].size = 0;
                    break;
                case 7: files2[k] = arr7[j];
                    arr7[j].size = 0;
                    break;
                case 8: files2[k] = arr8[j];
                    arr8[j].size = 0;
                    break;
                case 9: files2[k] = arr9[j];
                    arr9[j].size = 0;
                    break;
                }
                k++;
            }
            count[i] = 0;
        }
        digit = digit * 10;
    } while (ind == 1);
    free(arr0);
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);
    free(arr6);
    free(arr7);
    free(arr8);
    free(arr9);
}

void main()
{
    char directory[200];
    struct _finddata_t* files;
    intptr_t hFile;
    double time_of_starting, time_of_ending, time_of_sort;
    short answer;
    int i = 0, j = 0;
    files = (struct _finddata_t*)malloc(sizeof(struct _finddata_t) * 1);
    setlocale(LC_ALL, "Rus");
    printf("Добрый день!\n");
    do
    {
        printf("Введите путь до директории, файлы которой нужно отсортировать:\t");
        scanf_s("%s", directory, 200);
        strcat(directory, "/*.*");
        if ((hFile = _findfirst(directory, &c_file)) != -1L)
        {
            i = 0;
            do
            {
                if (c_file.size >= 0)
                    i++;
            } while (_findnext(hFile, &c_file) == 0);

            _findclose(hFile);
            files = (struct _finddata_t*)malloc(i * sizeof(struct _finddata_t));
            if ((hFile = _findfirst(directory, &c_file)) != -1L)
            {
                i = 0;
                do
                {
                    if (c_file.size >= 0)
                    {
                        files[i] = c_file;
                        i++;
                    }
                } while (_findnext(hFile, &c_file) == 0);
                _findclose(hFile);
                printf("Количество файлов в данной директории: %d\n", i);
            }
            files2 = (struct _finddata_t*)malloc(i * sizeof(struct _finddata_t));
            do
            {
                printf("Введите номер метода сортировки (чтобы выбрать сортировку 'пузырьком' введите '1', сотрировку 'выбором' - '2', сотрировку 'вставками' - '3', сотрировку 'слиянием' - '4', сотрировку 'Хоара' - '5', сотрировку 'Шелла' - '6', сотрировку 'подсчетом' - '7'(возможна только при максимальном размере файла в 10000 байт), сортировку 'поразрядную' - '8'):\t");
                answer = 0;
                scanf_s("%hi", &answer);
                while (getchar() != '\n');
                switch (answer)
                {
                case 1: answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    bubble_sort(i);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                case 2: answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    select_sort(i);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                case 3: answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    insert_sort(i);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                case 4: answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    merge_sort(0, i - 1);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                case 5: answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    quick_sort(0, i - 1);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                case 6: answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    shell_sort(i);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                case 7: while ((j < i) && (files[j].size < 10000)) j++;
                    if (i > j)
                    {
                        printf("Данный метод сортировки не пременим к выбранной директории\n");
                        break;
                    }
                    answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    counting_sort(i);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                case 8: answer = increase_or_decrease();
                    if (answer == 3)
                        break;
                    copy_arrays(files, i);
                    time_of_starting = omp_get_wtime();
                    radix_sort(i);
                    time_of_ending = omp_get_wtime();
                    time_of_sort = time_of_ending - time_of_starting;
                    if (answer == 1)
                        print_of_table_increase(i);
                    else print_of_table_decrease(i);
                    printf("Время сортировки: %lf с\n", time_of_sort);
                    answer = 3;
                    break;
                default: printf("Метод сортировки введен некорректно\n");
                    break;
                }
                printf("Что Вы хотите сделать далее? Отсортировать файлы в директории иным способом (введите '1'), перейти в другую директорию (введите '2') или закончить сортировку (введите любой символ кроме '1' и '2')\t");
                scanf_s("%hi", &answer);
            } while (answer == 1);
            free(files);
            free(files2);
        }
        else
        {
            printf("Путь до директории введен некорректно\nХотите ли Вы попробовать ввести путь до директории заново? (если да, введите '2', если нет - любой другой символ)\t");
            scanf_s("%hi", &answer);
        }
    } while (answer == 2);
    printf("Спасибо, что использовали файловый менеджер. Хорошего Вам дня!\n");
    system("pause");
}