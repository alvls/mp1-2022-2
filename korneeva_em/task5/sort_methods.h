#pragma once
#include "sort_algorithms.h"

struct SortMethod
{
    char name[16];
    SortAlgorithm func;
};
struct SortMethod sort_methods[] = {
    {"Пузырьковая", bubble_sort},
    {"Выбором", select_sort},
    {"Вставками", insert_sort},
    {"Слиянием", merge_sort},
    {"Быстрая", quick_sort},
    {"Шелла", increment_sort},
    {"Подсчётом", count_sort},
};
#define AVAILABLE_SORT_METHODS (int)(sizeof(sort_methods) / sizeof(struct SortMethod))