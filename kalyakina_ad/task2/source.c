#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
void main()
{
    setlocale(LC_ALL, "Rus");
    char r;
    int n, n2, i = 0, k = 0;
    char answer;
    printf("Введите номер режима ");
    scanf_s("%c", &r);
    if (r == '1')//Режим 1
    {
        srand(time(NULL));//Для получения при каждом вызове rand() нового числа
        n = 1 + rand() % (1000);
        while (k != n)
        {
            printf("Введите Ваш вариант ");
            scanf_s("%d", &k);
            if (k < n) printf("Загаданное число больше ");
            else if (k > n) printf("Загаданное число меньше ");
            i++;
        }
        printf("Угадали! Ваше количество попыток: %d \n", i);
    }
    else if (r == '2')//Режим 2
    {
        n = 0;//Левая граница
        n2 = 1001;//Правая граница
        k = 500;
        i = 1;
        scanf_s("%c", &answer);
        printf("%d Ваш ответ ", k);
        while (answer != '=')
        {
            if ((answer != '>') && (answer != '<') && (answer != '='))
                scanf_s("%c", &answer);
            else
            {
                if (answer == '>')
                {
                    n = k;
                    k = (n + n2) / 2;
                }
                else if (answer == '<')
                {
                    n2 = k;
                    k = (n + n2) / 2;
                };
                printf("%d Ваш ответ ", k);
                scanf_s("%c", &answer);
                i++;
            };
        }
        printf("Ура! Количество попыток: %d \n", i);
    }
    else printf("Неправильно введен номер режима ");
    system("pause");
}