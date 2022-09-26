#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

void main()
{
    setlocale(LC_ALL, "Russian");
    int guess, mode, answer, guesses = 0, local_min = 1, local_max = 1000;
    char sign, block;
    printf("Введите номер режима игры (1 или 2): ");
    scanf_s("%d", &mode);
    if (mode == 1)
    {
        printf("\nАктивирован режим игры \"Программа загадывает случайное число\"\n");
        printf("  Правила игры:\nПрограмма загадывает число от 1 до 1000, а вы пытаетесь его угадать. \nПрограмма будет подсказывать больше число или меньше.\n\n");
        srand(time(0));
        answer = (rand() % local_max) + local_min;
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
                printf("\n\nВы угадали\n");
            }
            guesses++;
        } while (guess != answer);
        printf("**********************\n");
        printf("Количество попыток: %d\n", guesses);
        printf("**********************\n\n");
    }
    else if (mode == 2)
    {
        printf("\nАктивирован режим игры \"Программа угадывает загаданное число\"\n");
        printf("  Правила игры:\nВы загадваете число, а программа пытается его угадать по определенному алгоритму.\nВы должны подсказывать знаком \">\" если загаданное число больше, \"<\" оно меньше и \"=\" если программа угадала\n\n");
        printf("Введите число, которое будет угадывать программа: ");
        scanf_s("%d", &answer);
        srand(time(0));
        do
        {
            guess = round((local_max - local_min) / 2) + local_min;
            printf("Ответ программы: %d\n", guess);
            printf("Введите \">\" или \"<\" или \"=\": ");
            scanf_s("%c", &block, 1);
            scanf_s("%c", &sign, 1);
            if (sign == '<')
                local_max = guess;
            else if (sign == '>')
                local_min = guess;
            guesses++;
        } while (sign != '=');
        printf("\n\nПрограмма угадала\n");
        printf("**********************\n");
        printf("Количество попыток: %d\n", guesses);
        printf("**********************\n\n");
    }
    //неверный ввод
    else
        printf("Введен неверный режим игры\n");
    //пауза в конце
    system("pause");
}