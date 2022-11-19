#include <stdlib.h>
#include "sort_algorithms.h"

void merge(struct _finddata_t* arr, size_t* iarr, int asc, size_t lb, size_t split, size_t ub)
{
    size_t pos1 = lb, pos2 = split + 1, pos3 = 0;

    size_t* temp = malloc(sizeof(size_t) * (ub - lb + 1));
    if (!temp)
    {
        printf("\nОшибка: недостаточно памяти для сортировки слиянием :(\n");
        return;
    }

    while (pos1 <= split && pos2 <= ub)
    {
        if ((arr[iarr[pos1]].size < arr[iarr[pos2]].size) == asc)
        {
            temp[pos3++] = iarr[pos1++];
        }
        else
        {
            temp[pos3++] = iarr[pos2++];
        }
    }

    while (pos2 <= ub)
    {
        temp[pos3++] = iarr[pos2++];
    }
    while (pos1 <= split)
    {
        temp[pos3++] = iarr[pos1++];
    }

    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
    {
        iarr[lb + pos3] = temp[pos3];
    }

    free(temp);
}

void merge_sort_internal(struct _finddata_t* arr, size_t* iarr, int asc, size_t lb, size_t ub)
{
    if (lb >= ub)
    {
        return;
    }

    size_t split = (lb + ub) / 2;

    merge_sort_internal(arr, iarr, asc, lb, split);
    merge_sort_internal(arr, iarr, asc, split + 1, ub);
    merge(arr, iarr, asc, lb, split, ub);
}

void merge_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc)
{
    merge_sort_internal(arr, iarr, asc, 0, len - 1);
}