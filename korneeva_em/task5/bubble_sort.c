#include "sort_algorithms.h"

void bubble_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc)
{
    size_t i, j;
    size_t tmp;

    for (i = 0; i < len; i++)
    {
        for (j = len - 1; j > i; j--)
        {
            if ((arr[iarr[j - 1]].size > arr[iarr[j]].size) == asc)
            {
                tmp = iarr[j - 1];
                iarr[j - 1] = iarr[j];
                iarr[j] = tmp;
            }
        }
    }
}