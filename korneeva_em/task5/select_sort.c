#include "sort_algorithms.h"

void select_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc)
{
    size_t i, j, k;
    size_t tmp;

    for (i = 0; i < len; i++)
    {
        k = i;
        tmp = iarr[i];

        for (j = i + 1; j < len; j++)
        {
            if ((arr[iarr[j]].size < arr[tmp].size) == asc)
            {
                k = j;
                tmp = iarr[j];
            }
        }

        iarr[k] = iarr[i];
        iarr[i] = tmp;
    }
}