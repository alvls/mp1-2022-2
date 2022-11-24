#include "Header.h"

void merge(struct _finddata_t* data_set, long lb, long split, long rb)
{
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    struct _finddata_t* temp = malloc(sizeof(struct _finddata_t) * (rb - lb + 1));
    while (pos1 <= split && pos2 <= rb) {
        if (data_set[pos1].size < data_set[pos2].size)
            temp[pos3++] = data_set[pos1++];
        else
            temp[pos3++] = data_set[pos2++];
    }
    while (pos2 <= rb)
        temp[pos3++] = data_set[pos2++];
    while (pos1 <= split)
        temp[pos3++] = data_set[pos1++];
    for (pos3 = 0; pos3 < rb - lb + 1; pos3++)
        data_set[lb + pos3] = temp[pos3];
    free(temp);
}

void mergeSort(struct _finddata_t* data_set, long lb, long rb) {
    long split;                  
    if (lb < rb) {               
        split = (lb + rb) / 2;

        mergeSort(data_set, lb, split);       // сортировать левую половину 
        mergeSort(data_set, split + 1, rb);// сортировать правую половину 
        merge(data_set, lb, split, rb);    // слить результаты в общий массив
    }
}
