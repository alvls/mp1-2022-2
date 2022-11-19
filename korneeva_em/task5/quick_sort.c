#include "sort_algorithms.h"

void quick_sort_internal(struct _finddata_t* arr, size_t iarr[], int asc, size_t lo, size_t hi)
{
    if (lo >= hi)
    {
        return;
    }

    struct _finddata_t pivot = arr[iarr[lo + (hi - lo) / 2]];
    size_t i = lo - 1, j = hi + 1, t;

    while (1)
    {
        if (asc)
        {
            while (arr[iarr[++i]].size < pivot.size);
            while (arr[iarr[--j]].size > pivot.size);
        }
        else
        {
            while (arr[iarr[++i]].size > pivot.size);
            while (arr[iarr[--j]].size < pivot.size);
        }
        if (i >= j)
        {
            break;
        }

        t = iarr[i];
        iarr[i] = iarr[j];
        iarr[j] = t;
    }

    quick_sort_internal(arr, iarr, asc, lo, j);
    quick_sort_internal(arr, iarr, asc, j + 1, hi);
}

void quick_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc)
{
    quick_sort_internal(arr, iarr, asc, 0, len - 1);
}