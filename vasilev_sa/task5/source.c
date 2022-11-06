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

#define SIZE_MENU 8
#define SIZE_ARR 20


enum KeysEnum 
{
	ESCAPE = 27, UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13, SPACE = 32, DEL = 8,
};
enum MenuEnum
{
	BUBBLE = 0, SELECT = 1, INSERTS = 2, MERGE = 3, HOARE = 4, SHELL = 5, COUNT = 6, EXIT = 7,
};

char Menu[SIZE_MENU][10] = { 
	"Пузырьком", "Выбором", "Вставками", "Слиянием", "Хоара", "Шелла", "Подсчётом", "Выход",
};

void print_info(struct _finddata_t* time_buf, int count);
void bubble_sort(struct _finddata_t* time_buf, int count);
void select_sort(struct _finddata_t* time_buf, int count);
void insert_sort(struct _finddata_t* time_buf, int count);
void merge_sort(struct _finddata_t* time_buf, int count);
void hoare_sort(struct _finddata_t* time_buf, int count);
void shell_sort(struct _finddata_t* time_buf, int count);
void count_sort(struct _finddata_t* time_buf, int count);

void main()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hidecursor();
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle("Сортировка файлов");
	system("cls");
	//---------------------------------------------------------
	struct _finddata_t c_file;
	struct _finddata_t* file_buf = malloc(sizeof(c_file));
	struct _finddata_t* time_buf;
	intptr_t hFile;
	int buf_count = 1;
	//---------------------------------------------------------
	int count = -2;
	char path[] = "c:\\temp\\*.*";
	if ((hFile = _findfirst(path, &c_file)) == -1L)
	{
		printf("No files in current directory!\n");
	}
	else
	{
		do 
		{
			if (count >= 0)
			{
				struct _finddata64i32_t* tmp = realloc(file_buf, sizeof(c_file) * (buf_count + count));
				if (tmp != NULL)
				{
					file_buf = tmp;
					file_buf[count] = c_file;
				}
				
			}
			count++;
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
	//---------------------------------------------------------
	char ch;
	int active_menu = 0;
	while (1)
	{
		//------------------------------------------------------------
		gotoxy(0, 0);
		textcolor(MAGENTA);
		printf("Методы сортировки: ");
		for (int i = 0; i < SIZE_MENU; i++)
		{
			if (i == active_menu)
				textcolor(LIGHTGREEN);
			else
				textcolor(LIGHTGRAY);
			gotoxy(1, i + 1);
			printf("> %s", Menu[i]);
		}
		//------------------------------------------------------------
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
			for (int i = 0; i < count; i++)
				time_buf[i] = file_buf[i];
			switch (active_menu)
			{
			case BUBBLE:
				clrscr();
				printf("Пузырьковая сортировка\n");
				bubble_sort(time_buf, count);
				break;
			case SELECT:
				clrscr();
				printf("Сортировка выбором\n");
				select_sort(time_buf, count);
				break;
			case INSERTS:
				clrscr();
				printf("Сортировка вставками\n");
				insert_sort(time_buf, count);
				break;
			case MERGE:
				clrscr();
				printf("Сортировка слиянием\n");
				merge_sort(time_buf, count);
				break;
			case HOARE:
				clrscr();
				printf("Сортировка Хоара\n");
				hoare_sort(time_buf, count);
				break;
			case SHELL:
				clrscr();
				printf("Сортировка Шелла\n");
				shell_sort(time_buf, count);
				break;
			case COUNT:
				clrscr();
				printf("Сортировка подсчётом\n");
				count_sort(time_buf, count);
				break;
			case EXIT:
				exit(0);
			}
			print_info(time_buf, count);
			active_menu = 0;
			system("pause");
			clrscr();
			free(time_buf);
			break;
		}
	}
}

//вывести данные отсортированного массива
void print_info(struct _finddata_t* time_buf, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("%d\n", time_buf[i].size);
	}
}
//пузырьковая сортировка
void bubble_sort(struct _finddata_t* time_buf, int count)
{
	struct _finddata_t temp;
	//--------------------------------------------------
	for (int i = 0; i < count; i++)
	{
		for (int j = count - 1; j > i; j--)
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
void select_sort(struct _finddata_t* time_buf, int count) 
{
	int index;
	struct _finddata_t temp;
	//--------------------------------------------------
	for (int i = 0; i < count; i++)
	{
		index = i;
		temp = time_buf[i];
		for (int j = i + 1; j < count; j++)
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
void insert_sort(struct _finddata_t* time_buf, int count)
{
	int j;
	struct _finddata_t temp;
	//--------------------------------------------------
	for (int i = 0; i < count; i++)
	{
		temp = time_buf[i];
		for (j = i - 1; j >= 0 && time_buf[j].size > temp.size; j--)
			time_buf[j + 1] = time_buf[j];
		time_buf[j + 1] = temp;
	}
}
//сортировка слиянием
void merge_sort(struct _finddata_t* time_buf, int count)
{
	//struct _finddata_t temp;
	//--------------------------------------------------

}
//сортировка Хоара
void hoare_sort(struct _finddata_t* time_buf, int count)
{
	//struct _finddata_t temp;
	//--------------------------------------------------

}
//сортировка Шелла
void shell_sort(struct _finddata_t* time_buf, int count)
{
	//struct _finddata_t temp;
	//--------------------------------------------------

}
//сортировка подсчётом
void count_sort(struct _finddata_t* time_buf, int count)
{
	//struct _finddata_t temp;
	//--------------------------------------------------

}
