#include "Header.h"
#include <io.h>

void quickSortR(struct _finddata_t* data_set, long size) {

    struct _finddata_t tmp, element;
    long leftboard[100] = { 0 }, rightboard[100] = {0};
    int mid, i, j;
    int position = 1;
    int left, right;
    leftboard[0] = 0;
    rightboard[0] = size - 1;
    

    do {
        left = leftboard[position];
        right = rightboard[position];
        position--;
        
        do {
            mid = (left + right) / 2;
            i = left;
            j = right;
            element = data_set[mid];

            do {
                while (data_set[i].size < element.size)
                    i++;
                while (element.size < data_set[j].size)
                    j--;
                if (i <= j) {
                    tmp = data_set[i];
                    data_set[i] = data_set[j];
                    data_set[j] = tmp;
                    i++;
                    j--;
                }
            } while (i <= j);
            if (i < mid) {
                if (i < right) {
                    position++;
                    leftboard[position] = i;
                    rightboard[position] = right;
                }
                right = j;
            }
            else {
                if (j > left) {
                    position++;
                    leftboard[position] = left;
                    rightboard[position] = j;
                }
                left = i;
            }
        } while (left < right);
    } while (!position);
}