#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <string.h>
#include "omp.h"
//сортировка пузырьком
void bubble_sort(struct _finddata_t* arr, int size)
{
	int i, j, c;
	struct _finddata_t tmp;
	for (i = 0;i < size - 1;i++)
	{
		c = 0;
		for (j = size - 1;j > i;j--)
			if (arr[j - 1].size > arr[j].size)
			{
				c++;
				tmp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = tmp;
			}
		if (c == 0)
			break;
	}
}
//сортировка выбором
void choice_sort(struct _finddata_t* arr, int size)
{
	int i, j, min_ind;
	struct _finddata_t tmp;
	for (i = 0; i < size;i++)
	{
		min_ind = i;
		for (j = i + 1;j < size;j++)
			if (arr[j].size < arr[min_ind].size)
				min_ind = j;
		tmp = arr[min_ind];
		arr[min_ind] = arr[i];
		arr[i] = tmp;
	}
}
//сортировка вставками
void insert_sort(struct _finddata_t* arr, int size)
{
	int i, j;
	struct _finddata_t tmp;
	for (i = 0;i < size;i++)
	{
		tmp = arr[i];
		for (j = i - 1;j >= 0 && arr[j].size > tmp.size;j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = tmp;
	}
}
//сортировка слиянием
void merge(struct _finddata_t* arr, int left, int middle, int right)
{
	int i, j, k;
	i = left;
	j = middle + 1;
	k = 0;
	int size = right - left + 1;
	struct _finddata_t* merge_arr = malloc(sizeof(struct _finddata_t) * size);
	while (i <= middle && j <= right)
	{
		if (arr[i].size < arr[j].size)
			merge_arr[k++] = arr[i++];
		else
			merge_arr[k++] = arr[j++];
	}
	while (j <= right)
		merge_arr[k++] = arr[j++];
	while (i <= middle)
		merge_arr[k++] = arr[i++];
	for (k = 0; k < size; k++)
		arr[left + k] = merge_arr[k];
	free(merge_arr);
}
void merge_sort(struct _finddata_t* arr, int left, int right)
{
	int middle = (left + right) / 2;
	if (left == right)
		return;
	if (left < right)
	{
		merge_sort(arr, left, middle);
		merge_sort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}
//быстрая сортировка
void quick_sort(struct _finddata_t* arr, int size)
{
	int l = 0;
	int r = size - 1;
	struct _finddata_t tmp, p;
	p = arr[size / 2];
	do
	{
		while (arr[l].size < p.size)
			l++;
		while (arr[r].size > p.size)
			r--;
		if (l <= r)
		{
			tmp = arr[l];
			arr[l] = arr[r];
			arr[r] = tmp;
			l++;
			r--;
		}
	} while (l <= r);
	if (r > 0)
		quick_sort(arr, l);
	if (l < size)
		quick_sort(arr + l, size - l);
}
//сортировка шелла
int increment(int* arr, int size)
{
	int p1, p2, p3, s;
	p1 = p2 = p3 = 1;
	s = -1;
	do
	{
		if (++s % 2)
			arr[s] = 8 * p1 - 6 * p2 + 1;
		else
		{
			arr[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 3;
		}
		p1 *= 2;
	} while (3 * arr[s] < size);
	return s > 0 ? --s : 0;
}
void shell_sort(struct _finddata_t* arr, int size)
{
	struct _finddata_t tmp;
	int inc, i, j, s;
	int* seq;
	seq = (int*)malloc(sizeof(int) * size);
	s = increment(seq, size);
	while (s >= 0)
	{
		inc = seq[s--];
		for (i = inc;i < size;i++)
		{
			tmp = arr[i];
			for (j = i - inc;(j >= 0) && (arr[j].size > tmp.size);j -= inc)
				arr[j + inc] = arr[j];
			arr[j + inc] = tmp;
		}
	}
	free(seq);
}
//сортировка подсчетом
void count_sort(struct _finddata_t* arr, int size)
{
	long int max_el = 0;
	long int min_el = arr[0].size;
	int k = 0, size_of_count;
	struct _finddata_t* copy = (struct _finddata_t*)malloc(sizeof(struct _finddata_t) * size);
	for (int i = 0;i < size;i++)
	{
		if (arr[i].size <= min_el)
			min_el = arr[i].size;
		if (arr[i].size >= max_el)
			max_el = arr[i].size;
		copy[i] = arr[i];//создание копии
	}
	size_of_count = max_el - min_el + 1;
	long int* c = (long int*)malloc(size_of_count * sizeof(long int));
	memset(c, 0, size_of_count * sizeof(long int));
	for (int i = 0;i < size;i++)
		c[arr[i].size - min_el]++;
	for (int i = 0;i < size_of_count;i++)
	{
		while (c[i] > 0)
		{
			for (int j=0;j<size;j++)
				if (min_el + i == copy[j].size)
				{
					arr[k++] = copy[j];
					c[i]--;
					break;
				}
		}
	}
	free(copy);
	free(c);
}
int main()
{
	struct _finddata_t c_file;
	struct _finddata_t* list_of_files;
	struct _finddata_t* sort;
	intptr_t hFile;
	char catalog[100];
	int answer;
	int sort_type;
	int count = 0, k = 0, f;
	double t1 = 0, t2 = 0;
	system("chcp 1251");
	system("cls");
	while (1)
	{
		printf("Введите путь до заданного каталога в формате c:\\...\\... : ");
		scanf_s("%s", catalog, 100);
		system("cls");
		strcat_s(catalog, 100, "\\*.*");
		if ((hFile = _findfirst(catalog, &c_file)) == -1L)
		{
			printf("В выбранном каталоге нет файлов\n");
			printf("Ввести другой путь? 1 - да/0 -  нет: ");
			scanf_s("%d", &answer);
			if (answer != 1)
			{
				system("cls");
				break;
			}
		}
		else
		{
			printf("\t\t\tСПИСОК ФАЙЛОВ:\n");
			printf("FILE                      DATE %24c   SIZE\n", ' ');
			printf("----                      ---- %24c   ----\n", ' ');
			do
			{
				char buffer[30];
				ctime_s(buffer, _countof(buffer), &c_file.time_write);
				printf("%-25.25s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
				count++;
			} while (_findnext(hFile, &c_file) == 0);
			printf("\nКол-во файлов: %d\n", count);
			list_of_files = (struct _finddata_t*)malloc(sizeof(struct _finddata_t) * count);
			sort = (struct _finddata_t*)malloc(sizeof(struct _finddata_t) * count);
			hFile = _findfirst(catalog, &c_file);
			do
			{
				if (k < count)
				{
					list_of_files[k] = c_file;
					k++;
				}
			} while (_findnext(hFile, &c_file) == 0);
			_findclose(hFile);
			while (1)
			{
				//выбор метода сортировки
				printf("\n\tВыберете метод сортировки:\n1 - сортировка пузырьком\n2 - сортировка выбором\n3 - сортировка вставками\n4 - сортировка слиянием\n5 - быстрая сортировка\n6 - сортировка Шелла\n7 - сортировка подсчетом\nВведите номер выбранного метода сортировки: ");
				scanf_s("%d", &sort_type);
				system("cls");
				//создание копии
				for (int i = 0;i < count;i++)
					sort[i] = list_of_files[i];
				f = 0;
				switch (sort_type)
				{
				case 1:
					t1 = omp_get_wtime();
					bubble_sort(sort, count);
					t2 = omp_get_wtime();
					break;
				case 2:
					t1 = omp_get_wtime();
					choice_sort(sort, count);
					t2 = omp_get_wtime();
					break;
				case 3:
					t1 = omp_get_wtime();
					insert_sort(sort, count);
					t2 = omp_get_wtime();
					break;
				case 4:
					t1 = omp_get_wtime();
					merge_sort(sort, 0, count - 1);
					t2 = omp_get_wtime();
					break;
				case 5:
					t1 = omp_get_wtime();
					quick_sort(sort, count);
					t2 = omp_get_wtime();
					break;
				case 6:
					t1 = omp_get_wtime();
					shell_sort(sort, count);
					t2 = omp_get_wtime();
					break;
				case 7:
					t1 = omp_get_wtime();
					count_sort(sort, count);
					t2 = omp_get_wtime();
					break;
				default:
					printf("Введен недопустимый номер сортировки\n");
					f = 1;
					break;
				}
				if (f == 0)
				{
					printf("\t\tОТСОРТИРОВАННЫЙ СПИСОК ФАЙЛОВ:\n");
					printf("FILE                      DATE %24c   SIZE\n", ' ');
					printf("----                      ---- %24c   ----\n", ' ');
					for (int i = 0;i < count;i++)
					{
						char buffer1[30];
						ctime_s(buffer1, _countof(buffer1), &sort[i].time_write);
						printf("%-25.25s %.24s  %10ld\n", sort[i].name, buffer1, sort[i].size);
					}
					printf("\nВремя сортировки: %lf (с)\n", t2 - t1);
					printf("\nОтсортировать другим методом? 1 - да/0 - нет: ");
					scanf_s("%d", &answer);
					if (answer != 1)
						break;
				}
				
			}
			free(list_of_files);
			free(sort);
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}