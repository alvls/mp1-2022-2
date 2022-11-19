#include "sort_algorithms.h"

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

void increment_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc)
{
    long inc, i, j, seq[40];
    int s;

    s = increment(seq, len);

    size_t tmp;
    while (s >= 0)
    {
        inc = seq[s--];

        for (i = inc; i < len; i++)
        {
            tmp = iarr[i];
            for (j = i - inc; (j >= 0) && ((arr[iarr[j]].size > arr[tmp].size) == asc); j -= inc)
            {
                iarr[j + inc] = iarr[j];
            }
            iarr[j + inc] = tmp;
        }
    }
}