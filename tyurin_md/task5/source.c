#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  
#include <io.h>  
#include <windows.h>
#include "Header.h"
#include <locale.h>
#include <time.h>
#include <omp.h>

#define SIZE 8
#define MAXSTACK 1024

SMALL_RECT window;
COORD buf;

enum KEYS {
   UP = 72, DOWN = 80, ENTER = 13
};

enum Sorting_Selection {
   Bubble = 0, Choice = 1, Inserts = 2, Merge = 3, Hoara = 4, Shell = 5, Tally = 6, EXIT = 7
};

char Menu[8][30] = { 
   "Сортировка \"Пузырьком\"", 
   "Сортировка \"Выбором\"", 
   "Сортировка \"Вставками\"", 
   "Сортировка \"Слиянием\"", 
   "Сортировка \"Хоара\"", 
   "Сортировка \"Шелла\"", 
   "Сортировка \"Подсчетом\"", 
   "Выход" 
};
int active_menu = 0;
char path[200];
int flag;


void BubbleSort(struct _finddata_t* time_arr, long size);
void ChoiceSort(struct _finddata_t* time_arr, long size);
void InsertsSort(struct _finddata_t* time_arr, long size);
void merge(struct _finddata_t* time_arr, long left, long split, long right);
void MergeSort(struct _finddata_t* time_arr, long left, long right);
void HoaraSort(struct _finddata_t* time_arr, long size);
long increment(long inc[], long size);
void ShellSort(struct _finddata_t* time_arr, long size);
_fsize_t Max_element(struct _finddata_t* time_arr, long size);
void TallySort(struct _finddata_t* time_arr, long size);
void print_arr(struct _finddata_t* time_arr, long count, double time);


void main()
{
   struct _finddata_t c_file;
   struct _finddata_t* directory;
   struct _finddata_t* time_arr;
   intptr_t hFile;

   setlocale(LC_ALL, "Russian");
   system("chcp 1251");
   SetConsoleTitle("Сортировщик файлов");
   textbackground(BLACK);
   setwindow(170, 70);
   SMALL_RECT window;
   COORD buf;
   getwindow(&window, &buf);

   char ch;
   double start, end;
   long size;
   long count;
   int variable_x;
   variable_x = (window.Left + window.Right) / 30;
   while (1)
   {
      size = 0;
      count = 0;

      system("cls");
      textcolor(MAGENTA);
      gotoxy(variable_x + 35, wherey() + 12);
      printf("Добро пожаловать в тестировщик файлов!\n");
      gotoxy(variable_x + 30, wherey()+1);
      printf("Введите путь к папке (d:/Folder/): ");
      scanf_s("%s", path, 200);
      strcat_s(path, 200, "*.*");
      if ((hFile = _findfirst(path, &c_file)) == -1L)
      {
         system("cls");
         textcolor(RED);
         gotoxy(variable_x + 35, wherey() + 12);
         printf("В папке нет файлов или не верный путь\n");
         gotoxy(variable_x + 35, wherey());
         system("pause");
      }
      else
      {
         do
         {
            if (c_file.size > 0)
               size++;
         } while (_findnext(hFile, &c_file) == 0);

         directory = calloc(size, sizeof(struct _finddata_t));

         hFile = _findfirst(path, &c_file);
         do
         {
            if (c_file.size > 0)
               directory[count++] = c_file;
         } while (_findnext(hFile, &c_file) == 0);
         _findclose(hFile);
         break;
      }
   }
   while (1) {
      hidecursor();
      system("cls");
      for (int i = 0; i < SIZE; i++) {
         if (i == active_menu)
            textcolor(GREEN);
         else 
            textcolor(YELLOW);
         printf("%s\n", Menu[i]);
      }
      ch = _getch();
      if (ch == -32) 
         ch = _getch(); 

      switch(ch)
      {
      case UP:
         if (active_menu > 0)
            active_menu--;
         break;
      case DOWN:
         if (active_menu < SIZE - 1)
            active_menu++;
         break;
      case ENTER:
         time_arr = calloc(size, sizeof(struct _finddata_t));
         if (!time_arr)
            return;
         for (long i = 0; i < size; i++)
            time_arr[i] = directory[i];
         switch (active_menu)
         {
         case Bubble:
            start = omp_get_wtime();
            BubbleSort(time_arr, size);
            end = omp_get_wtime();
            print_arr(time_arr, size, end - start);
            break;

         case Choice:
            start = omp_get_wtime();
            ChoiceSort(time_arr, size);
            end = omp_get_wtime();
            print_arr(time_arr, size, end - start);
            break;

         case Inserts:
            start = omp_get_wtime();
            InsertsSort(time_arr, size);
            end = omp_get_wtime();
            print_arr(time_arr, size, end - start);
            break;

         case Merge:
            start = omp_get_wtime();
            MergeSort(time_arr, 0, size - 1);
            end = omp_get_wtime();
            print_arr(time_arr, size, end - start);
            break;

         case Hoara:
            start = omp_get_wtime();
            HoaraSort(time_arr, size);
            end = omp_get_wtime();
            print_arr(time_arr, size, end - start);
            break;

         case Shell:
            start = omp_get_wtime();
            ShellSort(time_arr, size);
            end = omp_get_wtime();
            print_arr(time_arr, size, end - start);
            break;

         case Tally:
            flag = 0;
            start = omp_get_wtime();
            TallySort(time_arr, size);
            end = omp_get_wtime();
            if (flag == 0)
               print_arr(time_arr, size, end - start);
            break;

         case EXIT:
            exit(0);
            break;
         }
         free(time_arr);
         break;
      }
   }
}

void BubbleSort(struct _finddata_t* time_arr, long size)
{
   int i, j;
   struct _finddata_t tmp;
   for (i = 0; i < size; i++) {
      for (j = size - 1; j > i; j--) {
         if (time_arr[j - 1].size > time_arr[j].size) {
            tmp = time_arr[j];
            time_arr[j] = time_arr[j - 1];
            time_arr[j - 1] = tmp;
         }
      }
   }
}

void ChoiceSort(struct _finddata_t* time_arr, long size) {
   long i, j, k;
   struct _finddata_t tmp;

   for (i = 0; i < size; i++) {   	// i - номер текущего шага
      k = i;
      tmp = time_arr[i];
   
      for (j = i + 1; j < size; j++) { 	// цикл выбора наименьшего элемента
         if (time_arr[j].size < tmp.size) {
            k = j;
            tmp = time_arr[j];	        // k - индекс наименьшего элемента
         }
      }


      time_arr[k] = time_arr[i];
      time_arr[i] = tmp;   	// меняем местами наименьший с a[i]
      
   }
}

void InsertsSort(struct _finddata_t* time_arr, long size) {
   struct _finddata_t tmp;
   long i, j;

   for (i = 0; i < size; i++) {  // цикл проходов, i - номер прохода
      tmp = time_arr[i];

      // поиск места элемента в готовой последовательности 
      for (j = i - 1; (j >= 0) && (time_arr[j].size > tmp.size); j--)
         time_arr[j + 1] = time_arr[j];  	// сдвигаем элемент направо, пока не дошли

      time_arr[j + 1] = tmp;
   }
}

void merge(struct _finddata_t* time_arr, long left, long split, long right){
   long pos1 = left;
   long pos2 = split + 1;
   long pos3 = 0;

   struct _finddata_t* temp_arr = calloc((unsigned long long)(right - left + 1), sizeof(struct _finddata_t));

   if (!temp_arr)
      return;

   // идет слияние, пока есть хоть один элемент в каждой последовательности
   while ((pos1 <= split) && (pos2 <= right)) {
      if (time_arr[pos1].size < time_arr[pos2].size)
         temp_arr[pos3++] = time_arr[pos1++];
      else
         temp_arr[pos3++] = time_arr[pos2++];
   }

   while (pos2 <= right)   // пока вторая последовательность непуста 
      temp_arr[pos3++] = time_arr[pos2++];
   while (pos1 <= split)  // пока первая последовательность непуста
      temp_arr[pos3++] = time_arr[pos1++];

   for (pos3 = 0; pos3 < right - left + 1; pos3++)
      time_arr[left + pos3] = temp_arr[pos3];

   free(temp_arr);
}

void MergeSort(struct _finddata_t* time_arr, long left, long right) {
   long split;

   if (left < right) { 

      split = (left + right) / 2;

      MergeSort(time_arr, left, split); 
      MergeSort(time_arr, split + 1, right); 
      merge(time_arr, left, split, right);    
   }
}

void HoaraSort(struct _finddata_t* time_arr, long size) {
  
   struct _finddata_t tmp;
   struct _finddata_t pivot;
   long i, j; 
   long left, right; 

   long lbstack[MAXSTACK] = { 0 }, ubstack[MAXSTACK] = { 0 };
   long stackpos = 1;   	// текущая позиция стека
   long mid;

   lbstack[1] = 0;
   ubstack[1] = size - 1;

   do {

      left = lbstack[stackpos];
      right = ubstack[stackpos];
      stackpos--;

      do {
         
         mid = (left + right) / 2;
         i = left;
         j = right; 
         pivot = time_arr[mid];

         do {
            while (time_arr[i].size < pivot.size) 
               i++;
            while (pivot.size < time_arr[j].size) 
               j--;

            if (i <= j) {
               tmp = time_arr[i];
               time_arr[i] = time_arr[j];
               time_arr[j] = tmp;
               i++;
               j--;
            }
         } while (i <= j);

         if (i < mid) {  

            if (i < right) { 
               stackpos++;
               lbstack[stackpos] = i;
               ubstack[stackpos] = right;
            }
            right = j;
         }

         else {

            if (j > left) {
               stackpos++;
               lbstack[stackpos] = left;
               ubstack[stackpos] = j;
            }
            left = i;
         }

      } while (left < right);

   } while (stackpos != 0);
}

long increment(long inc[], long size) {
   int p1, p2, p3, s;

   p1 = p2 = p3 = 1;
   s = -1;
   do {
      if (++s % 2) {
         inc[s] = 8 * p1 - 6 * p2 + 1;
      }
      else {
         inc[s] = 9 * p1 - 9 * p3 + 1;
         p2 *= 2;
         p3 *= 2;
      }
      p1 *= 2;
   } while (3 * inc[s] < size);

   return s > 0 ? --s : 0;
}

void ShellSort(struct _finddata_t* time_arr, long size) {
   long inc, i, j, seq[40];
   int s;
   struct _finddata_t tmp;

   // вычисление последовательности приращений
   s = increment(seq, size);
   while (s >= 0) {
      // сортировка вставками с инкрементами inc[] 
      inc = seq[s--];

      for (i = inc; i < size; i++) {
         tmp = time_arr[i];
         for (j = i - inc; (j >= 0) && (time_arr[j].size > tmp.size); j -= inc)
            time_arr[j + inc] = time_arr[j];
         time_arr[j + inc] = tmp;
      }
   }
}

_fsize_t Max_element(struct _finddata_t* time_arr, long size) {
   _fsize_t max = 0;

   for (int i = 0; i < size; i++)
   {
      if (time_arr[i].size > max)
      {
         max = time_arr[i].size;
      }
   }

   return max;
}

void TallySort(struct _finddata_t* time_arr, long size)
{
   int i;
   int variable_x = (window.Left + window.Right) / 30;
   _fsize_t k = Max_element(time_arr, size);

   _fsize_t* cnt = malloc(sizeof(int) * (k + 1));
   if (!cnt) {
      flag = 1;
      system("cls");
      textcolor(RED);
      gotoxy(variable_x + 35, wherey() + 12);
      printf("Данная сортировка не поддерживает файлы данного размера\n");
      gotoxy(variable_x + 35, wherey());
      system("pause");
      return;
   }
   memset(cnt, 0, sizeof(int) * (k + 1));

   for (i = 0; i < size; i++)
   {
      cnt[time_arr[i].size]++;
   }

   for (i = 1; i <= k; i++)
   {
      cnt[i] += cnt[i - 1];
   }

   struct _finddata_t* res = malloc(sizeof(time_arr[0]) * size);
   if (!res) {
      flag = 1;
      system("cls");
      textcolor(RED);
      gotoxy(variable_x + 35, wherey() + 12);
      printf("Данная сортировка не поддерживает файлы данного размера\n");
      gotoxy(variable_x + 35, wherey());
      system("pause");
      return;
   }
   memset(res, 0, sizeof(time_arr[0]) * size);

   for (i = size - 1; i >= 0; i--)
   {
      res[cnt[time_arr[i].size] - 1] = time_arr[i];
      cnt[time_arr[i].size]--;
   }

   for (i = 0; i < size; i++)
   {
      time_arr[i] = res[i];
   }

   free(cnt);
   free(res);
}

void print_arr(struct _finddata_t* time_arr, long count, double time) {
   int variable_x, orderliness;
   variable_x = (window.Left + window.Right) / 30;
   showcursor();
   do {
      system("cls");
      textcolor(MAGENTA);
      gotoxy(variable_x + 15, wherey() + 12);
      printf("Выберите способ упорядоченности файлов (по возрастанию размера - 1, по убыванию размера - 2): ");
      scanf_s("%d", &orderliness);
   } while (orderliness != 1 && orderliness != 2);
   system("cls");
   gotoxy(variable_x + 50, wherey());
   printf("% s\n", Menu[active_menu]);
   printf("Название файла");
   gotoxy(variable_x + 70, wherey());
   printf("Размер\n");
   if (orderliness == 1) {
      for (long i = 0; i < count; i++)
      {
         textcolor(BLUE);
         gotoxy(variable_x, wherey());
         printf("%s", time_arr[i].name);
         gotoxy(variable_x + 70, wherey());
         printf("%ld байт\n", time_arr[i].size);
      }
   }
   else {
      for (long i = count - 1; i >= 0; i--)
      {
         textcolor(BLUE);
         gotoxy(variable_x, wherey());
         printf("%s", time_arr[i].name);
         gotoxy(variable_x + 70, wherey());
         printf("%ld байт\n", time_arr[i].size);
      }
   }

   gotoxy(variable_x, wherey() + 1);
   textcolor(MAGENTA);
   printf("Время выполнения сортировки %.15f секунд\n", time);
   textcolor(YELLOW);
   hidecursor();
   system("pause");
}
