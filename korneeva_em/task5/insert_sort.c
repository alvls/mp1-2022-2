#include "sort_algorithms.h"

void insert_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc)
{
    int i, j;
    size_t tmp;

    for (i = 0; i < len; i++)
    {
        tmp = iarr[i];

        for (j = i - 1; j >= 0 && (arr[iarr[j]].size > arr[tmp].size) == asc; j--)
        {
            iarr[j + 1] = iarr[j];
        }

        iarr[j + 1] = tmp;
    }
}