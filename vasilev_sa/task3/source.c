#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>


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
    int generate_number = 0, input_number, attempts = 0;
    short n, random_place, she_cow_count, he_cow_count, count;
    char ch;
    setlocale(LC_ALL, "Russian");
    do
    {
        system("cls");
        printf("Введите необходимое количество цифр (от 2 до 5): ");
        count = scanf_s("%hd", &n);
        while (ch = getchar() != '\n');
    } while ((n < 2) || (n > 5) || (count < 1));

    for (int i = 0; i < n; i++)
    {
        srand(time(0));
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

    printf("\nПравила игры:\nВы должны вводить числа так, как того просит программа, иначе она не примет ваши значения. \nЕсли вы хотите закончить попытку, то введите отрицательное число.\n\nНачало игры:\n");
    while (1)
    {
        he_cow_count = 0;
        she_cow_count = 0;
        attempts++;

        do
        {
            printf("%d попытка: Введите %d-значное число, где цифры не повторяются: ", attempts, n);
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
                            she_cow_count++;
                        
                    }
                }
            }
            if (he_cow_count == n)
                break;
            printf("Коров: %d\nБыков: %d\n", she_cow_count, he_cow_count);
        }
    }
    if (input_number >= 0)
    {
        printf("\n**********************\n");
        printf("Вы правы, ответ: %d\n", generate_number);
        printf("Количество попыток: %d\n", attempts);
        printf("**********************\n\n");
    }
    printf("\n");
    system("pause");
}