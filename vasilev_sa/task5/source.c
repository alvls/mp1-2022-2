#pragma warning(disable : 5105)

#include <stdio.h>
#include <omp.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <io.h>  
#include <time.h>
#include "header.h"


#define SIZE_MENU 9
#define MAX_STACK 1024

char PATH[200];
struct _finddata_t* file_buf;

enum KeysEnum 
{
	ESCAPE = 27, UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13, SPACE = 32, DEL = 8,
};
enum MenuEnum
{
	CH_PATH = 0, BUBBLE = 1, SELECT = 2, INSERTS = 3, MERGE = 4, HOARE = 5, SHELL = 6, COUNT = 7, EXIT = 8,
};

char Menu[SIZE_MENU][30] = { 
	"Сменить директорий",
	"Сортировка \"Пузырьком\"", 
	"Сортировка \"Выбором\"", 
	"Сортировка \"Вставками\"", 
	"Сортировка \"Слиянием\"", 
	"Сортировка \"Хоара\"", 
	"Сортировка \"Шелла\"", 
	"Сортировка \"Подсчётом\"", 
	"Выход", 
};

long found_dir(void);
void input_path(void);
void print_info(struct _finddata_t* time_buf, long count, double work_time);
void bubble_sort(struct _finddata_t* time_buf, long count);
void select_sort(struct _finddata_t* time_buf, long count);
void insert_sort(struct _finddata_t* time_buf, long count);
void merge(struct _finddata_t* time_buf, long left, long split, long right);
void merge_sort(struct _finddata_t* time_buf, long left, long right);
void quick_sort(struct _finddata_t* time_buf, long count);
long increment(long inc[], long count);
void shell_sort(struct _finddata_t* time_buf, long count);
unsigned long long max_elem(struct _finddata_t* time_buf, long count);
short count_sort(struct _finddata_t* time_buf, size_t count);

void main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle("Сортировка файлов");

	struct _finddata_t* time_buf;
	long count;
	char ch, print_path[200];
	long active_menu = 0;
	double start, end;
	short flag;

	count = found_dir();

	while (1)
	{
		gotoxy(0, 0);
		textcolor(WHITE);
		strncpy_s(print_path, 200, PATH, strlen(PATH) - 3);
		printf("Вы находитесь по адресу: %s\n", print_path);
		printf("Методы сортировки: ");
		for (long i = 0; i < SIZE_MENU; i++)
		{
			if (i == active_menu)
				textcolor(LIGHTGREEN);
			else
				textcolor(LIGHTGRAY);
			gotoxy(1, i + 2);
			printf("> %s", Menu[i]);
		}
		ch = _getch();
		if (ch == -32) 
			ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < SIZE_MENU - 1)
				++active_menu;
			break;
		case ESCAPE:
			free(file_buf);
			exit(0);
			break;
		case RIGHT:
		case ENTER:
		case SPACE:
			do
			{
				time_buf = calloc(count, sizeof(struct _finddata_t));
			} while (!time_buf);
			for (long i = 0; i < count; i++)
				time_buf[i] = file_buf[i];
			system("cls");
			textcolor(LIGHTGREEN);
			flag = 1;
			switch (active_menu)
			{
			case CH_PATH:
				count = found_dir();
				continue;
			case BUBBLE:
				printf("Пузырьковая сортировка\n");
				start = omp_get_wtime();
				bubble_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case SELECT:
				printf("Сортировка выбором\n");
				start = omp_get_wtime();
				select_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case INSERTS:
				printf("Сортировка вставками\n");
				start = omp_get_wtime();
				insert_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case MERGE:
				printf("Сортировка слиянием\n");
				start = omp_get_wtime();
				merge_sort(time_buf, 0, count - 1);
				end = omp_get_wtime();
				break;
			case HOARE:
				printf("Сортировка Хоара\n");
				start = omp_get_wtime();
				quick_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case SHELL:
				printf("Сортировка Шелла\n");
				start = omp_get_wtime();
				shell_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case COUNT:
				printf("Сортировка подсчётом\n");
				start = omp_get_wtime();
				flag = count_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case EXIT:
				exit(0);
			}
			if (flag)
				print_info(time_buf, count, end - start);
			else
			{
				textcolor(RED);
				printf("Не удалось выполнить сортировку, возможно данные в папке имеют слишком большой размер\n");
			}
			textcolor(WHITE);
			system("pause");
			system("cls");
			free(time_buf);
			break;
		}
	}
}

//найти папку по адресу
long found_dir(void)
{
	struct _finddata_t c_file;
	struct _finddata_t* tmp;
	intptr_t hFile;
	long count = 0, size = 0;
	showcursor();
	while (1)
	{
		input_path();
		if ((hFile = _findfirst(PATH, &c_file)) == -1L)
		{
			textcolor(RED);
			printf("Неверно введены данные!\n");
			textcolor(WHITE);
			system("pause");
			continue;
		}
		do
		{
			if (c_file.size > 0)
				size++;
		} while (_findnext(hFile, &c_file) == 0);
		if (size == 0)
		{
			textcolor(RED);
			printf("Папка пуста, либо в ней отсутствуют сортируемые по размеру файлы, выберите другую папку\n");
			textcolor(WHITE);
			system("pause");
			continue;
		}
		tmp = calloc(size, sizeof(struct _finddata_t));
		if (tmp != NULL)
			file_buf = tmp;
		else
			break;
		hFile = _findfirst(PATH, &c_file);
		do
		{
			if ((c_file.size > 0) && (count < size))
				file_buf[count++] = c_file;
		} while (_findnext(hFile, &c_file) == 0);

		_findclose(hFile);
		break;
	}
	hidecursor();
	return count;
}
//ввести адрес директории
void input_path(void)
{
	system("cls");
	textcolor(WHITE);
	printf("Введите путь до директории: (в формате c:/temp/)\n >>> ");
	textcolor(LIGHTGRAY);
	fgets(PATH, 200, stdin);
	PATH[strlen(PATH) - 1] = '\0';
	strcat_s(PATH, 200, "*.*");
	system("cls");
}
//вывести данные отсортированного массива
void print_info(struct _finddata_t* time_buf, long count, double work_time)
{
	textcolor(LIGHTGRAY);
	gotoxy(2, 1);
	printf("Название");
	gotoxy(51, 1);
	printf("Размер");
	for (long i = 0; i < count; i++)
	{
		gotoxy(1, 2 + i);
		printf("%s", time_buf[i].name);
		gotoxy(50, 2 + i);
		printf("%lld байт\n", (_int64)time_buf[i].size);
	}
	printf("Всего файлов: %ld\n", count);
	printf("Сортировка заняла %f секунд\n", work_time);
}
//пузырьковая сортировка
void bubble_sort(struct _finddata_t* time_buf, long count)
{
	struct _finddata_t temp;
	for (long i = 0; i < count; i++)
	{
		for (long j = count - 1; j > i; j--)
		{
			if (time_buf[j - 1].size > time_buf[j].size)
			{
				temp = time_buf[j - 1];
				time_buf[j - 1] = time_buf[j];
				time_buf[j] = temp;
			}
		}
	}
}
//сортировка выбором
void select_sort(struct _finddata_t* time_buf, long count) 
{
	long index;
	struct _finddata_t temp;
	for (long i = 0; i < count; i++)
	{
		index = i;
		temp = time_buf[i];
		for (long j = i + 1; j < count; j++)
		{
			if (time_buf[j].size < temp.size)
			{
				index = j;
				temp = time_buf[j];
			}
		}
		time_buf[index] = time_buf[i];
		time_buf[i] = temp;
	}
}
//сортировка вставками
void insert_sort(struct _finddata_t* time_buf, long count)
{
	long j;
	struct _finddata_t temp;
	for (long i = 0; i < count; i++)
	{
		temp = time_buf[i];
		for (j = i - 1; j >= 0 && time_buf[j].size > temp.size; j--)
			time_buf[j + 1] = time_buf[j];
		time_buf[j + 1] = temp;
	}
}
//подфункция к merge_sort
void merge(struct _finddata_t* time_buf, long left, long split, long right)
{
	long pos1, pos2, pos3;
	pos1 = left;
	pos2 = split + 1;
	pos3 = 0;
	struct _finddata_t* temp_buf = calloc((unsigned long long)(right - left + 1), sizeof(struct _finddata_t));
	if (!temp_buf)
		return;
	while ((pos1 <= split) && (pos2 <= right))
	{
		if (time_buf[pos1].size < time_buf[pos2].size)
			temp_buf[pos3++] = time_buf[pos1++];
		else
			temp_buf[pos3++] = time_buf[pos2++];
	}
	while (pos2 <= right)
		temp_buf[pos3++] = time_buf[pos2++];
	while (pos1 <= split)
		temp_buf[pos3++] = time_buf[pos1++];
	for (pos3 = 0; pos3 < right - left + 1; pos3++)
		time_buf[left + pos3] = temp_buf[pos3];
	free(temp_buf);
}
//сортировка слиянием
void merge_sort(struct _finddata_t* time_buf, long left, long right)
{
	if (left < right)
	{
		long split = (left + right) / 2;
		merge_sort(time_buf, left, split);
		merge_sort(time_buf, split + 1, right);
		merge(time_buf, left, split, right);
	}
}
//сортировка Хоара
void quick_sort(struct _finddata_t* time_buf, long count)
{
	long i, j;
	long left, right;
	long lstack[MAX_STACK] = { 0 }, rstack[MAX_STACK] = { 0 };
	long stackpos = 1;
	long middle;
	struct _finddata_t temp, elem;
	lstack[1] = 0;
	rstack[1] = count - 1;
	
	do
	{
		left = lstack[stackpos];
		right = rstack[stackpos];
		stackpos--;

		do
		{
			middle = (right + left) / 2;
			i = left;
			j = right;
			elem = time_buf[middle];

			do
			{
				while (time_buf[i].size < elem.size)
					i++;
				while (elem.size < time_buf[j].size)
					j--;

				if (i <= j)
				{
					temp = time_buf[i];
					time_buf[i] = time_buf[j];
					time_buf[j] = temp;
					i++;
					j--;
				}
			} while (i <= j);

			if (i < middle)
			{
				if (i < right)
				{
					stackpos++;
					lstack[stackpos] = i;
					rstack[stackpos] = right;
				}
				right = j;
			}
			else
			{
				if (j > left)
				{
					stackpos++;
					lstack[stackpos] = left;
					rstack[stackpos] = j;
				}
				left = i;
			}
		} while (left < right);
	} while (stackpos != 0);
}
//подфункция shell_sort
long increment(long inc[], long count)
{
	long p1 = 1, p2 = 1, p3 = 1, s = -1;
	do
	{
		if (++s % 2)
			inc[s] = 8 * p1 - 6 * p2 + 1;
		else
		{
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[s] < count);
	return s > 0 ? --s : 0;
}
//сортировка Шелла
void shell_sort(struct _finddata_t* time_buf, long count)
{
	long inc, i, j, seq[40];
	long s;
	s = increment(seq, (long)count);
	while (s >= 0)
	{
		inc = seq[s--];
		for (i = inc; i < count; i++)
		{
			struct _finddata_t temp = time_buf[i];
			for (j = i - inc; (j >= 0) && (time_buf[j].size > temp.size); j -= inc)
				time_buf[j + inc] = time_buf[j];
			time_buf[j + inc] = temp;
		}
	}
}
//подфункция count_sort
unsigned long long max_elem(struct _finddata_t* time_buf, long count)
{
	unsigned long long max = 0;
	for (long i = 0; i < count; i++)
	{
		if ((long)time_buf[i].size > max)
			max = time_buf[i].size;
	}
	return max;
}
//сортировка подсчётом
short count_sort(struct _finddata_t* time_buf, size_t count)
{
	_fsize_t max_size = 0;
	for (int i = 0; i < count; i++)
		if (time_buf[i].size > max_size)
			max_size = time_buf[i].size;
	if (max_size > 1500000000)
		return 0;
	_fsize_t* size_buf = calloc((unsigned long long)(max_size) + 1, sizeof(long));
	if (size_buf == NULL)
		return 0;
	for (int i = 0; i < count; i++)
		size_buf[time_buf[i].size]++;
	for (int i = 1; i <= (int)max_size; i++)
		size_buf[i] += size_buf[i - 1];
	struct _finddata_t* answer_buf = calloc(count, sizeof(time_buf[0]));
	if (answer_buf == NULL)
		return 0;
	for (int i = (int)count - 1; i >= 0; i--)
	{
		answer_buf[size_buf[time_buf[i].size] - 1] = time_buf[i];
		size_buf[time_buf[i].size]--;
	}
	for (int i = 0; i < count; i++)
		time_buf[i] = answer_buf[i];
	free(size_buf);
	free(answer_buf);
	return 1;
}
