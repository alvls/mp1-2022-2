#pragma once
#include <io.h>

struct _finddata_t* data_set;

int menu();
void reverse(struct _finddata_t* data_set, int size);
void bubbleSort(struct _finddata_t* data_set, int size);
void insertSort(struct _finddata_t* data_set, long count);
void mergeSort(struct _finddata_t* data_set, long lb, long rb);
void shellSort(struct _finddata_t* data_set, long size);
void selectSort(struct _finddata_t* data_set, int count);
void quickSortR(struct _finddata_t* data_set, int size);
void countingSort(struct _finddata_t* data_set, _fsize_t count);
