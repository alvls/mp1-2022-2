#include <stdlib.h>
#include "sort_algorithms.h"

void count_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc)
{
    _fsize_t k = arr[0].size;
    for (size_t i = 1; i < len; i++)
    {
        if (arr[i].size > k)
        {
            k = arr[i].size;
        }
    }

    if (k == 0)
    {
        return;
    }

    _fsize_t* cnt = malloc(sizeof(_fsize_t) * (k + 1));
    if (!cnt)
    {
        printf("\nОшибка: недостаточно памяти для сортировки подсчётом :(\n");
        return;
    }
    memset(cnt, 0, sizeof(_fsize_t) * (k + 1));

    size_t i;

    for (i = 0; i < len; i++)
    {
        cnt[arr[i].size]++;
    }

    if (asc)
    {
        for (i = 1; i <= k; i++)
        {
            cnt[i] += cnt[i - 1];
        }
    }
    else
    {
        for (i = k; i-- > 0; )
        {
            cnt[i] += cnt[i + 1];
        }
    }

    for (i = 0; i < len; i++)
    {
        iarr[cnt[arr[i].size] - 1] = i;
        cnt[arr[i].size]--;
    }

    free(cnt);
}