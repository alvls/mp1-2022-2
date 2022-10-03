#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <math.h>


void main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    //обьявление переменных и констант
    const short many = 20;

    short all_numbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    short robot_array[5] = { 0, 0, 0, 0, 0 };
    short human_array[5] = { 0, 0, 0, 0, 0 };
    int generate_number = 0;
    int input_number = 0;
    short n = 4, random_place;
    short she_cow_count = 0, he_cow_count = 0;
    int guesses = 0;
    // генерация случайного n-значного числа
    for (int i = 0; i < n; i++)
    {
        back:
        random_place = rand() % 10;
        if (all_numbers[random_place] < 10)
        {
            if ((i == 0) && (random_place == 0))
            {
                robot_array[i] = 1;
                all_numbers[1] = many;
            }
            else
            {
                robot_array[i] = all_numbers[random_place];
                all_numbers[random_place] = many;
            }
        }
        else
            goto back;
    }
    //массив робота в сгенерированное число
    for (int k = 0; k < n; k++)
        generate_number += robot_array[k] * pow(10, n - k - 1);
    
    //быки и коровы
    while (he_cow_count < 4)
    {
        he_cow_count = 0;
        she_cow_count = 0;
        guesses++;
        printf("%d попытка: Введите %d-значное число: ", guesses, n);
        scanf_s(" %d", &input_number);
        //число человека в массив
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
        printf("Коров: %d\nБыков: %d\n", she_cow_count, he_cow_count);
    } 
    printf("\n**********************\n");
    printf("Вы угадали");
    printf("Количество попыток: %d\n", guesses);
    printf("**********************\n\n");
    system("pause");
}