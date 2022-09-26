#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

void main()
{
    //локализация
    setlocale(LC_ALL, "Russian");
    //объявление переменных
    const int MIN = 1, MAX = 1000;
    int guess = 0, guesses = 0, answer, local_min = 1, local_max = 1000, mode;
    char sign, stop;
    //режимы игры
    printf("Введите номер режима игры (1 или 2): ");
    scanf_s("%d", &mode);
    //первый режим
    if (mode == 1)
    {
        printf("\nАктивирован режим игры \"Программа загадывает случайное число\"\n\n");
        //генерация случайного числа между MIN и MAX
        srand(time(0));
        answer = (rand() % MAX) + MIN;
        //цикл угадывания
        do {
            printf("Введите предположение: ");
            scanf_s("%d", &guess);
            if (guess > answer)
            {
                printf("Загаданное число меньше\n\n");
            }
            else if (guess < answer)
            {
                printf("Загаданное число больше\n\n");
            }
            else {
                printf("\n\n\tВерно!\n");
            }
            guesses++;
        } while (guess != answer);
        printf("**********************\n");
        printf("Ответ: %d\n", answer);
        printf("Количество попыток: %d\n", guesses);
        printf("**********************\n\n");
    }
    //второй режим
    else if (mode == 2)
    {
        printf("\nАктивирован режим игры \"Робот угадывает загаданное число\"\n\n");
        printf("Введите число, которое будет угадывать робот: ");
        scanf_s("%d", &answer);
        srand(time(0));
        do
        {
            guess = round((local_max - local_min) / 2) + local_min;
            printf("Ответ робота: %d\n", guess);
            printf("Введите > или < или =: ");
            scanf_s("%c", &stop, 1);
            scanf_s("%c", &sign, 1);
            if (sign == '<')
                local_max = guess;
            else if (sign == '>')
                local_min = guess;
            guesses++;
        } while (sign != '=');
        printf("\n\n\tВерно!\n");
        printf("**********************\n");
        printf("Ответ: %d\n", answer);
        printf("Количество попыток: %d\n", guesses);
        printf("**********************\n\n");
    }
    //неверный ввод
    else
        printf("Введен неверный режим игры\n");
    //пауза в конце
    system("pause");
}