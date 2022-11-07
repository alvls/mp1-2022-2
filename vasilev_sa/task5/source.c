#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <memory.h>
#include <string.h>
#include <io.h>  
#include <time.h>
#include "header.h"

#define SIZE_MENU 9
#define SIZE_ARR 20
#define MAX_STACK 1024

char PATH[200] = "c:/temp/*.*";

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

void input_path();
void print_info(struct _finddata_t* time_buf, long count);
void bubble_sort(struct _finddata_t* time_buf, long count);
void select_sort(struct _finddata_t* time_buf, long count);
void insert_sort(struct _finddata_t* time_buf, long count);
void merge(struct _finddata_t* time_buf, long left, long split, long right);
void merge_sort(struct _finddata_t* time_buf, long left, long right);
void hoare_sort(struct _finddata_t* time_buf, long count);
long increment(long inc[], long count);
void shell_sort(struct _finddata_t* time_buf, long count);
unsigned long long max_elem(struct _finddata_t* time_buf, long count);
void count_sort(struct _finddata_t* time_buf, long count);

void main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle("Сортировка файлов");
	struct _finddata_t* file_buf = malloc(sizeof(struct _finddata_t));
	struct _finddata_t* time_buf;
	//---------------------------------------------------------
	struct _finddata_t c_file;
	intptr_t hFile;
	long buf_count = 1;
  long count = 0;

	while(1)
	{
		input_path();
		if ((hFile = _findfirst(PATH, &c_file)) == -1L)
		{
			printf("No files in current directory!\n");
			system("pause");
			continue;
		}
		do
		{
			if (c_file.attrib != 16)
			{
				struct _finddata_t* tmp = realloc(file_buf, sizeof(struct _finddata_t) * (unsigned long long)(buf_count + count));
				if (tmp != NULL)
				{
					file_buf = tmp;
					file_buf[count] = c_file;
					count++;
				}
			}
			
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
		break;
	}

	char ch;
	long active_menu = 0;
	hidecursor();
	while (1)
	{
		gotoxy(0, 0);
		textcolor(MAGENTA);
		printf("Методы сортировки: ");
		for (long i = 0; i < SIZE_MENU; i++)
		{
			if (i == active_menu)
				textcolor(LIGHTGREEN);
			else
				textcolor(LIGHTGRAY);
			gotoxy(1, i + 1);
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
		case RIGHT:
		case ENTER:
		case SPACE:
			time_buf = calloc(count, sizeof(c_file));
			if (!time_buf)
			{
				free(time_buf);
				return;
			}
			for (long i = 0; i < count; i++)
				time_buf[i] = file_buf[i];
			clrscr();
			switch (active_menu)
			{
			case CH_PATH:

			case BUBBLE:
				printf("Пузырьковая сортировка\n");
				bubble_sort(time_buf, count);
				break;
			case SELECT:
				printf("Сортировка выбором\n");
				select_sort(time_buf, count);
				break;
			case INSERTS:
				printf("Сортировка вставками\n");
				insert_sort(time_buf, count);
				break;
			case MERGE:
				printf("Сортировка слиянием\n");
				merge_sort(time_buf, 0, count - 1);
				break;
			case HOARE:
				printf("Сортировка Хоара\n");
				hoare_sort(time_buf, count);
				break;
			case SHELL:
				printf("Сортировка Шелла\n");
				shell_sort(time_buf, count);
				break;
			case COUNT:
				printf("Сортировка подсчётом\n");
				count_sort(time_buf, count);
				break;
			case EXIT:
				exit(0);
			}
			print_info(time_buf, count);
			system("pause");
			clrscr();
			free(time_buf);
			break;
		}
	}
}

//ввести адрес директории
void input_path()
{
	clrscr();
	printf("Введите путь до директории: (в формате c:/temp/)\n");
	fgets(PATH, 200, stdin);
	PATH[strlen(PATH) - 1] = '\0';
	strcat_s(PATH, 200, "*.*");
	clrscr();
}
//вывести данные отсортированного массива
void print_info(struct _finddata_t* time_buf, long count)
{
	for (long i = 0; i < count; i++)
	{
		printf("%s: %d байт | %d\n", time_buf[i].name, time_buf[i].size, time_buf[i].attrib);
	}
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
void hoare_sort(struct _finddata_t* time_buf, long count)
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
	long p1, p2, p3, s;

	p1 = p2 = p3 = 1;
	s = -1;
	do
	{
		if (++s % 2)
		{
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
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
void count_sort(struct _finddata_t* time_buf, long count)
{
	
	//struct _finddata_t* temp_buf;
	for (long i = 0; i < count; i++);

}
