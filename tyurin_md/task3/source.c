#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void main() {
  setlocale(LC_ALL, "Russian");
  int n, cows, bulls;
  int random_location, number = 0, entered_number;
  int all_numbers[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
  int robot_number[5] = { 0, 0, 0, 0, 0 }, user_number[5] = { 0, 0, 0, 0, 0 };
  char ch;

  do {
     printf("Выберите длину загадаваемого числа(от 2 до 5): ");
     scanf_s("%d", &n);
  } while ((n < 2) || (n > 5));
  system("cls");
  printf("Добро пожаловать в игру \"Быки и коровы\"\n");
  printf("Вам необходимо выбрать длину загадываемого числа, после чего компьютер загадывает число, которое вам необходимо отгадать\n");
  printf("\nКомрьютер сообщит: \n1) сколько цифр угадано без совпадения с их позицией(то есть коров)\n2) сколько угадано цифр вплоть до позиции(то есть быков)\n");

  for (int i = 0; i < n; i++) {
    srand(time(NULL));
    beginning:
    random_location = rand() % 10;
    if (all_numbers[random_location] < 10) {
      if ((random_location == 0) && (i == 0))
        goto beginning;
      else {
        robot_number[i] = all_numbers[random_location];
        all_numbers[random_location] = 1000;
      }
    }
    else
      goto beginning;
  }

  for (int j = 0; j < n; j++) {
     number += robot_number[j] * (int)pow(10, n - j - 1);
  }

  printf("\n\tЧтобы завершить игру введите 0\n\n");
  do {
    cows = 0;
    bulls = 0;
    do {
       while (ch = getchar() != '\n');
       printf("Введите число длинной %d: ", n);
       scanf_s("%d", &entered_number);
       if (entered_number == 0)
          goto finish;
    } while (entered_number < pow(10, n - 1) || entered_number >= pow(10, n));
    for (int m = 1; m < n + 1; m++) {
      user_number[n - m] = entered_number % 10;
      entered_number /= 10;
    }
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < n; k++) {
        if (robot_number[i] == user_number[k]) {
          if (i == k)
            bulls++;
          else
            cows++;
        }
      }
    }
    printf("Число коров = %d\nЧисло быков = %d\n", cows, bulls);
  } while (bulls != n);
  printf("Поздравляю, ты отгадал число!\n");

  finish:
  if (bulls != n)
     printf("Ответ: %d\n", number);

  system("PAUSE");
}
