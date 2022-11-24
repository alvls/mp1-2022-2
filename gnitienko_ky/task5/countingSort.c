#include <math.h>
#include <stdlib.h>
#include "Header.h"

void countingSort(struct _finddata_t* data_set, size_t count) {
    int i;
    _fsize_t buf = max_file_size(data_set, count);
    _fsize_t* k = malloc(sizeof(int) * (buf + 1));
    memset(k, 0, sizeof(int) * (buf + 1));
    for (i = 0; i < count; i++)
        k[data_set[i].size]++;

    for (i = 1; i <= buf; i++)
        k[i] += k[i - 1];

    struct _finddata_t* temp = malloc(sizeof(data_set[0]) * count);
    memset(temp, 0, sizeof(sizeof(data_set[0])) * count);
    for (i = count - 1; i >= 0; i--) {
        temp[k[data_set[i].size] - 1] = data_set[i];
        k[data_set[i].size]--;
    }

    for (i = 0; i < count; i++)
        data_set[i] = temp[i];
    free(k);
    free(temp);
}