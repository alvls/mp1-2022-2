#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
void main()
{
    int number, num_ent, count, regime, minimum, maximum;
    char op;
	setlocale(LC_ALL, "Rus");
	printf("Выберете режим игры: введите 1 или 2 \n");
	scanf_s("%i", &regime);
	if (regime == 1)
	{
		srand(time(NULL));
		number = (1 + rand() % 1000);
		num_ent = 0;
		count = 0;
		while (num_ent != number)
		{
			printf("Угадайте число: ");
			scanf_s("%i", &num_ent);
			count += 1;
			if (num_ent < number)
				printf("Загаданное число больше \n");
			else if (num_ent > number)
				printf("Загаданное число меньше \n");
			else if (num_ent == number)
			{
				printf("Вы угадали!!! \n");
			}
		}
		printf("Количесво попыток: %i \n", count);
	}
	if (regime == 2)
	{
		printf("Загадайте число: ");
		scanf_s("%i", &number);
		num_ent = 500;
		count = 0;
		minimum = 0;
		maximum = 1000;
		while (1)
		{
			printf("Вы загадали число (введите >, <, =)  %i \n", num_ent);
			scanf_s(" %c", &op);
			count += 1;
			if (op == '>')
			{
				minimum = num_ent;
				num_ent = (num_ent + maximum) / 2;
			}
			else if (op == '<')
			{
				maximum = num_ent;
				num_ent = (num_ent + minimum) / 2;
			}
			else if (op == '=')
			{
				printf("Ваше число отгадано: %i \n", num_ent);
				printf("Количество попыток: %i \n", count);
				break;
			}
		}
	}
	system("pause");
}