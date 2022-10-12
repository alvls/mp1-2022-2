#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include "Header.h"


int check_conditions(int input_number, short n, short count)
{
  short array[5] = { 0 };
  if (input_number < 0)
      return 0;
  if (count < 1)
      return 1;
  if ((input_number < pow(10, n - 1)) || (input_number >= pow(10, n)))
      return 1;
  for (int k = 0; k < n; k++)
  {
      array[n - k - 1] = input_number % 10;
      input_number /= 10;
  }
  for (int i = 0; i < n; i++)
  {
      for (int j = 0; j < n; j++)
      {
          if ((array[i] == array[j]) & (i != j))
              return 1;
      }
  }
  if (array[0] == 0)
      return 1;
  return 0;
}

void main()
{
  const short many = 20;
  short all_digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, robot_array[5] = { 0, 0, 0, 0, 0 }, human_array[5] = { 0, 0, 0, 0, 0 };
  int generate_number = 0, input_number, attempts = 0, time_x, time_y;
  short n, random_place, she_cow_count, he_cow_count, count;
  char ch;
  //начальные настройки
  setlocale(LC_ALL, "Russian");
  textbackground(BLACK);
  setwindow(80, 30);
  SMALL_RECT window;
  COORD buf;
  getwindow(&window, &buf);
  //----------------------------------------------------
  do
  {
      clrscr();
      gotoxy((window.Left + window.Right) / 4 + 1, (window.Top + window.Bottom) / 10);
      textcolor(WHITE);
      printf("Добро пожаловать в игру ");
      textcolor(MAGENTA);
      printf("\"Быки и коровы\"");
      //----------------------------------------------------------------
      textcolor(WHITE);
      time_x = (window.Left + window.Right) / 20 - 1;
      gotoxy(time_x, wherey() + 2);
      printf("Цель игры - угадать число, состоящее из n - ого числа цифр.");
      gotoxy(time_x, wherey() + 1);
      printf("Программа загадывает число с неповторяющимися цифрами.");
      gotoxy(time_x, wherey() + 1);
      printf("Вы должны вводить числа, следую тому же правилу.");
      gotoxy(time_x, wherey() + 1);
      printf("Компьютер сообщит, сколько цифр угадано:");
      gotoxy(time_x + 1, wherey() + 1);
      printf("1) без совпадения с их позициями в загаданном числе (коровы).");
      gotoxy(time_x + 1, wherey() + 1);
      printf("2) вплоть до позиции в загаданном числе(быки).");
      gotoxy(time_x, wherey() + 1);
      textattr(RED);
      printf("P.S: неверные значения программа не примет!");
      gotoxy((window.Left + window.Right) / 6 - 2, (window.Top + window.Bottom) / 2);
      //------------------------------------------------------------------
      textcolor(GREEN);
      printf("Введите необходимое количество цифр (от 2 до 5): ");
      showcursor();
      textcolor(WHITE);
      count = scanf_s("%hd", &n);
      while (ch = getchar() != '\n');
  } while ((n < 2) || (n > 5) || (count < 1));
  // generation
  for (int i = 0; i < n; i++)
  {
      srand((unsigned int)time(NULL)); //может быть ошибка
      back:
      random_place = rand() % 10;
      if (all_digits[random_place] < 10)
      {
          if ((i == 0) && (random_place == 0))
          {
              robot_array[i] = 1;
              all_digits[1] = many;
          }
          else
          {
              robot_array[i] = all_digits[random_place];
              all_digits[random_place] = many;
          }
      }
      else
          goto back;
  }
  for (int k = 0; k < n; k++)
      generate_number += robot_array[k] * (int)pow(10, n - k - 1);

  time_x = (window.Left + window.Right) / 2 - 5;
  time_y = (window.Top + window.Bottom) / 2 - 1;
  while (1)
  {
    attempts++;
    do
    {
        clrscr();
        if (attempts > 1)
        {
          gotoxy(time_x, time_y + 2);
          printf("Коровы: %d", she_cow_count);
          gotoxy(time_x, time_y + 3);
          printf("Быки: %d", he_cow_count);
        } 
        gotoxy(time_x, time_y);
        textcolor(GREEN);
        printf("Попытка (%d): ", attempts);
        showcursor();
        textcolor(WHITE);
        count = scanf_s("%d", &input_number);
        while (ch = getchar() != '\n');
    } while (check_conditions(input_number, n, count));
    if (input_number < 0)
    {
        printf("Ответ: %d\n", generate_number);
        break;
    }
      
    else
    {
      he_cow_count = 0;
      she_cow_count = 0;
      for (int k = 0; k < n; k++)
      {
        human_array[n - k - 1] = input_number % 10;
        input_number /= 10;
      }
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          if (human_array[i] == robot_array[j])
          {
            if (i == j)
                he_cow_count++;
            else
                she_cow_count++;            }
        }
      }
      if (he_cow_count == n)
        break;
      printf("Коров: %d\nБыков: %d\n", she_cow_count, he_cow_count);
    }
  }
  if (input_number >= 0)
  {
    clrscr();
    printf("\n**********************\n");
    printf("Вы правы, ответ: %d\n", generate_number);
    printf("Количество попыток: %d\n", attempts);
    printf("**********************\n\n");
  }
  printf("\n");
  system("pause");
}
//int main()
//{
//    const int COUNT = 16 * 16;
//    SMALL_RECT window;
//    COORD buf;
//    getwindow(&window, &buf);
//    hidecursor();
//    //printf("%d %d %d %d", window.Left, window.Top, window.Right, window.Bottom);
//    setwindow(120, 250);
//    getchar();
//    textattr(LIGHTGRAY);
//
//    clrscr();
//
//    gotoxy(10, 10);
//    printf("test\n");
//
//    gotoxy(0, 12);
//    textattr(RED);
//    printf("abcd");
//    getchar();
//
//    gotoxy(2, 12);
//    textbackground(BLUE);
//    printf("cdef");
//    getchar();
//
//    gotoxy(4, 12);
//    textcolor(BLUE);
//    textbackground(YELLOW);
//    printf("efgh");
//
//    for (int i = 0; i < COUNT; i++)
//    {
//        textcolor(i);
//        textbackground(i / 16);
//        printf("a");
//    }
//
//    textattr(LIGHTGRAY);
//
//    int page = GetConsoleOutputCP();
//    printf("page = %d", page);
//    SetConsoleOutputCP(1251);
//
//    printf("press any key");
//    getchar();
//    setWindow(window, buf);
//
//    showcursor();
//
//    return 0;
//}
