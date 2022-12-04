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

//количество элементов в меню
#define SIZE_MENU 10
//максимальный размер стэка для сортировки Хоара
#define MAX_STACK 1024

//адрес папки
char PATH[200];
//порядок сортировки: 1 - по возрастанию, 0 - по убыванию
short sort_key = 1;
//массив с файлами из папки
struct _finddata_t* file_buf;
//коды клавиш для управления меню
enum KeysEnum
{
	ESCAPE = 27, UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13, SPACE = 32, DEL = 8, 
};
//для наглядности свича при выборе метода сортировки
enum MenuEnum
{
	BUBBLE, SELECT, INSERTS, MERGE, HOARE, SHELL, COUNT, CH_PATH, CHANGE, EXIT,
};
//цвета программы
typedef enum {
	TITLE = LIGHTMAGENTA, TEXT = LIGHTGRAY, CHOICE = LIGHTGREEN, PAUSE = LIGHTRED, WARNING = RED, TEXT_INP = WHITE
} ColorSettings;
//выводящееся на экран меню
char Menu[SIZE_MENU][40] = { 
	"Сортировка \"Пузырьком\"", 
	"Сортировка \"Выбором\"", 
	"Сортировка \"Вставками\"", 
	"Сортировка \"Слиянием\"", 
	"Сортировка \"Хоара\"", 
	"Сортировка \"Шелла\"", 
	"Сортировка \"Подсчётом\"",
	"Сменить директорий",
	"Сменить порядок сортировки",
	"Выход", 
};

//----------------------------Начало-объявления----------------------------

void reverse_arr(struct _finddata_t* time_buf, long count);
long found_dir(void);
void input_path(void);
void print_info(struct _finddata_t* time_buf, long count, double work_time, long active_menu);
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

//----------------------------Конец-объявления----------------------------

void main(void)
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
		strncpy_s(print_path, 200, PATH, strlen(PATH) - 3);
		textcolor(TITLE);
		if (sort_key)
			printf(" Сортировка по возрастанию ");
		else
			printf(" Сортировка по убыванию ");
		textcolor(CHOICE);
		printf("(%s):\n", print_path);
		for (long i = 0; i < SIZE_MENU; i++)
		{
			if (i == active_menu)
				textcolor(CHOICE);
			else
				textcolor(TEXT);
			gotoxy(1, i + 1);
			printf(">>> %s", Menu[i]);
		}
		ch = _getch();
		if (ch == -32) 
			ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu == 0)
				active_menu = SIZE_MENU - 1;
			else
				active_menu--;
			break;
		case DOWN:
			if (active_menu == SIZE_MENU - 1)
				active_menu = 0;
			else
				active_menu++;
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
			textcolor(CHOICE);
			flag = 1;
			switch (active_menu)
			{
			case CH_PATH:
				count = found_dir();
				active_menu = 0;
				continue;
			case BUBBLE:
				start = omp_get_wtime();
				bubble_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case SELECT:
				start = omp_get_wtime();
				select_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case INSERTS:
				start = omp_get_wtime();
				insert_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case MERGE:
				start = omp_get_wtime();
				merge_sort(time_buf, 0, count - 1);
				end = omp_get_wtime();
				break;
			case HOARE:
				start = omp_get_wtime();
				quick_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case SHELL:
				start = omp_get_wtime();
				shell_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case COUNT:
				start = omp_get_wtime();
				flag = count_sort(time_buf, count);
				end = omp_get_wtime();
				break;
			case CHANGE:
				if (sort_key)
					sort_key = 0;
				else
					sort_key = 1;
				system("cls");
				textcolor(TITLE);
				printf("Вы сменили порядок сортировки\n");
				textcolor(PAUSE);
				system("pause");
				system("cls");
				active_menu = 0;
				continue;
			case EXIT:
				exit(0);
			}
			if (flag)
			{
				reverse_arr(time_buf, count);
				print_info(time_buf, count, end - start, active_menu);
			}
			else
			{
				textcolor(RED);
				printf("Не удалось выполнить сортировку, возможно данные в папке имеют слишком большой размер\n");
			}
			textcolor(PAUSE);
			system("pause");
			system("cls");
			free(time_buf);
			break;
		}
	}
}

//----------------------------Начало-реализации-функций----------------------------

void reverse_arr(struct _finddata_t* time_buf, long count)
{
	if (!sort_key)
	{
		struct _finddata_t* temp = calloc(count, sizeof(struct _finddata_t));
		if (temp == NULL)
			return;
		for (int i = 0; i < count; i++)
			temp[count - i - 1] = time_buf[i];
		for (int i = 0; i < count; i++)
			time_buf[i] = temp[i];
	}
}
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
			textcolor(WARNING);
			printf("Неверно введены данные!\n");
			textcolor(PAUSE);
			system("pause");
			continue;
		}
		do
		{
			if (c_file.attrib != 16)
				size++;
		} while (_findnext(hFile, &c_file) == 0);
		if (size == 0)
		{
			textcolor(WARNING);
			printf("Папка пуста, либо в ней отсутствуют сортируемые по размеру файлы, выберите другую папку\n");
			textcolor(PAUSE);
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
			if ((c_file.attrib != 16) && (count < size))
				file_buf[count++] = c_file;
		} while (_findnext(hFile, &c_file) == 0);

		_findclose(hFile);
		break;
	}
	hidecursor();
	return count;
}
void input_path(void)
{
	system("cls");
	textcolor(TITLE);
	printf("Введите путь до директории: ");
	textcolor(CHOICE);
	printf("(в формате c:/папка/папка/)");
	textcolor(TEXT_INP);
	printf("\n >>> ");
	fgets(PATH, 200, stdin);
	PATH[strlen(PATH) - 1] = '\0';
	strcat_s(PATH, 200, "*.*");
	system("cls");
}
void print_info(struct _finddata_t* time_buf, long count, double work_time, long active_menu)
{
	textcolor(CHOICE);
	printf("\t\t\t%s", Menu[active_menu]);
	textcolor(TITLE);
	gotoxy(2, 1);
	printf("Название");
	gotoxy(53, 1);
	printf("Размер\n");
	printf(" --------------------------------------------------------------");
	for (long i = 0; i < count; i++)
	{
		gotoxy(1, 3 + i);
		textcolor(TITLE);
		printf("|");
		textcolor(TEXT);
		printf("%s", time_buf[i].name);
		gotoxy(45, 3 + i);
		textcolor(TITLE);
		printf("|");
		textcolor(TEXT);
		printf("%12lld байт", (_int64)time_buf[i].size);
		textcolor(TITLE);
		printf("|");
	}
	textcolor(TITLE);
	printf("\n --------------------------------------------------------------\n");
	printf(" Всего файлов: ");
	textcolor(CHOICE);
	printf("%ld шт.\n", count);
	textcolor(TITLE);
	printf(" Сортировка заняла: ");
	textcolor(CHOICE);
	printf("%f сек.\n", work_time);
	
}
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

//----------------------------Конец-реализации-функций----------------------------
