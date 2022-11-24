#include "Header.h"
#include <io.h>

void bubbleSort(struct _finddata_t* data_set, long size) {
    struct _finddata_t user;

    for (long i = 0; i < size; i++) {
        for (long j = size - 1; j > i; j--) {
            if (data_set[j - 1].size > data_set[j].size) {

                user = data_set[j - 1]; data_set[j - 1] = data_set[j]; data_set[j] = user;
            }
        }
    }
}