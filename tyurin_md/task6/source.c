#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "Header.h"

#define SIZE 2
#define SIZE_2 4

SMALL_RECT window;
COORD buf;


char Menu[SIZE][30] = {
   "1 режим",
   "2 режим"
};
char Menu_2[SIZE_2][30] = {
   "sin(x)",
   "cos(x)",
   "exp(x)",
   "arsh(x)"
};

enum KEYS {
   UP = 72, DOWN = 80, ENTER = 13, LEFT = 75,
};

enum Mode {
    mode_1 = 0, mode_2 = 1
};

double factorial(int N);
void MyExp(double x, double accuracy, int N, int mode);
void MySin(double x, double accuracy, int N, int mode);
void MyCos(double x, double accuracy, int N, int mode);
void MyArsh(double x, double accuracy, int N, int mode);
void Print_func(double standard, int i, int N, double answ, double difference, int mode);

int active_menu = 0, active_menu_2 = 0;
int variable_x;

void main() {
   void (*my_func[SIZE_2]) (double, double, int, int) = { MySin, MyCos, MyExp, MyArsh };
   setlocale(LC_ALL, "Russian");
   textbackground(BLACK);
   setwindow(170, 70);
   getwindow(&window, &buf);

   char c;
   double x = 0;
   double accuracy = 0;
   int N = 0;
   char ch;
   short flag;
   variable_x = (window.Left + window.Right) / 30;

   textcolor(MAGENTA);
   gotoxy(variable_x + 50, wherey() + 12);
   printf("Добро пожаловать!!!!\n");
   gotoxy(variable_x + 20, wherey() + 1);
   printf("Данная программа позволяет выполнять расчет значений для некоторого набора функций");
   gotoxy(variable_x + 18, wherey() + 1);
   printf("в заданной точке с заданной погрешностью за счет разложения этих функций в ряд Тейлора\n");
   textcolor(WHITE);
   gotoxy(variable_x + 40, wherey() + 1);
   system("pause");


   while (1) {
      hidecursor();
      system("cls");
      textcolor(YELLOW);
      printf("Выберите режим:\n");
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

      switch (ch)
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
         flag = 1;
         while (flag) {
            system("cls");
            for (int i = 0; i < SIZE_2; i++) {
               if (i == active_menu_2)
                  textcolor(GREEN);
               else
                  textcolor(YELLOW);
               printf("%s\n", Menu_2[i]);
            }
            ch = _getch();
            if (ch == -32)
               ch = _getch();

            switch (ch)
            {
            case UP:
               if (active_menu_2 > 0)
                  active_menu_2--;
               break;
            case DOWN:
               if (active_menu_2 < SIZE_2 - 1)
                  active_menu_2++;
               break;
            case LEFT:
               flag = 0;
               break;
            case ENTER:
               textcolor(MAGENTA);
               system("cls");
               showcursor();
               gotoxy(variable_x + 35, wherey() + 12);
               printf("Введите значение x (для arsh(x): |x| < 1): ");
               scanf_s("%lf", &x);
       
               switch (active_menu)
               {
               case mode_1:

                  do {
                     system("cls");
                     gotoxy(variable_x + 35, wherey() + 12);
                     printf("Введите точность вычисления (>= 0,000001): ");
                     scanf_s("%lf", &accuracy);
                     while (c = getchar() != '\n');
                  } while (accuracy < 0.000001);
                 
                  do {
                     system("cls");
                     gotoxy(variable_x + 30, wherey() + 12);
                     printf("Введите число элементов ряда для выполнения расчета (N - от 1 до 1000): ");
                     scanf_s("%d", &N);
                     while (c = getchar() != '\n');
                  } while ((N < 1) || (N > 1000));
                  break;

               case mode_2:

                  do {
                     system("cls");
                     gotoxy(variable_x + 30, wherey() + 12);
                     printf("Введите число экспериментов(NMax - от 1 до 25): ");
                     scanf_s("%d", &N);
                     while (c = getchar() != '\n');
                  } while ((N < 1) || (N > 25));
                  break;
               }
               hidecursor();
               my_func[active_menu_2](x, accuracy, N, active_menu);
               break;
            }
        }
      }
   }
}


double factorial(int N) {
   double F = 1;
   for (int i = 2; i <= N; i++)
      F *= i;
   return F;
}

void MyExp(double x, double accuracy, int N, int mode) {
   double answ = 0;
   double standard = exp(x);
   int i;
   system("cls");
   switch (mode)
   {
   case mode_1:
      for (i = 0; i < N; i++) {
         answ += (pow(x, i) / factorial(i));
         if (fabs(standard - answ) <= accuracy) {
            i++;
            break;
         }
      }
      Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      break;
   case mode_2:
      gotoxy(variable_x + 45, wherey());
      printf("Расчет функции %s \n", Menu_2[active_menu_2]);
      printf(" Эталонное значение: %lf\n", standard);
      printf(" Кол-во слагаемых\tВычисленная оценка значения функции\tРазница между оценкой и эталонным значением\n");
      for (i = 0; i <= N; i++) {
         answ += (pow(x, i) / factorial(i));
         Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      }
      break;
   }
   system("pause");
}

void MySin(double x, double accuracy, int N, int mode) {
   double answ = 0;
   double standard = sin(x);
   int i;
   system("cls");
   switch (mode)
   {
   case mode_1:
      for (i = 0; i < N; i++) {
         answ += ((pow(-1, i) * pow(x, (2 * i) + 1)) / factorial((2 * i) + 1));
         if (fabs(standard - answ) <= accuracy) {
            i++;
            break;
         }
      }
      Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      break;
   case mode_2:
      gotoxy(variable_x + 45, wherey());
      printf("Расчет функции %s \n", Menu_2[active_menu_2]);
      printf(" Эталонное значение: %lf\n", standard);
      printf(" Кол-во слагаемых\tВычисленная оценка значения функции\tРазница между оценкой и эталонным значением\n");
      for (i = 0; i <= N; i++) {
         answ += ((pow(-1, i) * pow(x, (2 * i) + 1)) / factorial((2 * i) + 1));
         Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      }
      break;
   }
   system("pause");
}

void MyCos(double x, double accuracy, int N, int mode) {
   double answ = 0;
   double standard = cos(x);
   int i;
   system("cls");
   switch (mode)
   {
   case mode_1:
      for (i = 0; i < N; i++) {
         answ += (pow(-1, i) * ((pow(x, (2 * i))) / factorial(2 * i)));
         if (fabs(standard - answ) <= accuracy) {
            i++;
            break;
         }
      }
      Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      break;
   case mode_2:
      gotoxy(variable_x + 45, wherey());
      printf("Расчет функции %s \n", Menu_2[active_menu_2]);
      printf(" Эталонное значение: %lf\n", standard);
      printf(" Кол-во слагаемых\tВычисленная оценка значения функции\tРазница между оценкой и эталонным значением\n");
      for (i = 0; i <= N; i++) {
         answ += ((pow(-1, i) * pow(x, (2 * i))) / factorial(2 * i));
         Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      }
      break;
   }
   system("pause");
}

void MyArsh(double x, double accuracy, int N, int mode) {
   double answ = 0;
   double standard = asinh(x);
   int i;
   system("cls");
   switch (mode)
   {
   case mode_1:
      for (i = 0; i < N; i++) {
         answ += ((((pow(-1, i)) * (factorial(2 * i))) / ((pow(4, i)) * (pow((factorial(i)), 2)) * ((2 * i) + 1))) * (pow(x, ((2 * i) + 1))));
         if (fabs(standard - answ) <= accuracy) {
            i++;
            break;
         }
      }
      Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      break;
   case mode_2:
      gotoxy(variable_x + 45, wherey());
      printf("Расчет функции %s \n", Menu_2[active_menu_2]);
      printf(" Эталонное значение: %lf\n", standard);
      printf(" Кол-во слагаемых\tВычисленная оценка значения функции\tРазница между оценкой и эталонным значением\n");
      for (i = 0; i < N; i++) {
         answ += (((pow(-1, i) * (factorial(2 * i))) / ((pow(4, i)) * (pow(factorial(i), 2)) * ((2 * i) + 1))) * (pow(x, ((2 * i) + 1))));
         Print_func(standard, i, N, answ, fabs(standard - answ), mode);
      }
      break;
   }
   system("pause");
}

void Print_func(double standard, int i, int N, double answ, double difference, int mode) {
   switch (mode)
   {
   case mode_1:
      textcolor(MAGENTA);
      gotoxy(variable_x + 45, wherey());
      printf("Расчет функции %s \n", Menu_2[active_menu_2]);
      textcolor(BLUE);
      printf("Эталонное значение:  %lf\n", standard);
      printf("Вычисленная оценка значения функции:  %lf\n", answ);
      printf("Разница между оценкой и эталонным значением:  %lf\n", fabs(standard - answ));
      printf("Количество слагаемых, которое было вычислено:  %d/%d\n\n", i, N);
      textcolor(WHITE);
      break;
   case mode_2:
      textcolor(BLUE);
      gotoxy(wherex() + 1, wherey());
      printf("%d", i + 1);
      gotoxy(variable_x + 21, wherey());
      printf("%lf", answ);
      gotoxy(variable_x + 61, wherey());
      printf("%lf\n", fabs(standard - answ));
      textcolor(WHITE);
      break;
   }
}