#include "Header.h"

void merge(struct _finddata_t* data_set, long lb, long split, long rb) {
    // Слияние упорядоченных частей массива в буфер temp
    // с дальнейшим переносом содержимого temp в a[lb]...a[ub]

      // текущая позиция чтения из первой последовательности a[lb]...a[split]
    long pos1 = lb;

    // текущая позиция чтения из второй последовательности a[split+1]...a[ub]
    long pos2 = split + 1;

    // текущая позиция записи в temp
    long pos3 = 0;

    struct _finddata_t* temp = (struct _finddata_t*)malloc((unsigned long long)(rb - lb + 1) * sizeof(struct _finddata_t));
    if (temp == NULL)
        return;
    // идет слияние, пока есть хоть один элемент в каждой последовательности
    while ((pos1 <= split) && (pos2 <= rb)) {
        if (data_set[pos1].size < data_set[pos2].size)
            temp[pos3++] = data_set[pos1++];
        else
            temp[pos3++] = data_set[pos2++];
    }

    // одна последовательность закончилась - 
    // копировать остаток другой в конец буфера 
    while (pos2 <= rb)   // пока вторая последовательность непуста 
        temp[pos3++] = data_set[pos2++];
    while (pos1 <= split)  // пока первая последовательность непуста
        temp[pos3++] = data_set[pos1++];

    // скопировать буфер temp в a[lb]...a[ub]
    for (pos3 = 0; pos3 < rb - lb + 1; pos3++)
        data_set[lb + pos3] = temp[pos3];
    free(temp);
}

void mergeSort(struct _finddata_t* data_set, long lb, long rb) {
    long split;                   // индекс, по которому делим массив

    if (lb < rb) {                // если есть более 1 элемента

        split = (lb + rb) / 2;

        mergeSort(data_set, lb, split);       // сортировать левую половину 
        mergeSort(data_set, split + 1, rb);// сортировать правую половину 
        merge(data_set, lb, split, rb);    // слить результаты в общий массив
    }
}
