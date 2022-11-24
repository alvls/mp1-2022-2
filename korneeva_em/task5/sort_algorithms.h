#pragma once

#include <stdio.h>  
#include <io.h>  

typedef void (*SortAlgorithm)(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);

void bubble_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);
void select_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);
void insert_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);
void merge_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);
void quick_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);
void increment_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);
void count_sort(struct _finddata_t* arr, size_t* iarr, size_t len, int asc);