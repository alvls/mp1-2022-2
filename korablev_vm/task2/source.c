#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>//инклюды
void main()
{
	setlocale(LC_ALL, "Rus");//локализация
	int mode=0, rn, SelectedNumber=0, AttemptsCount=0,c=500,mn=0,mx=1001,c1;
	char sn,enter;
	while ((mode < 1) || (mode>2))
	{
		printf("Выберите режим игры (1 - угадываете вы, 2 - угадывает программа) = ");
		scanf_s("%d", &mode);
	}
	if (mode==1)//первый режим
	{
		srand(time(NULL));
		rn = (rand() % 1000)+1;
		printf("Число загадано. Сделайте предположение, программа направит вас на верный путь ");
		while (SelectedNumber != rn)
		{
			scanf_s("%d", &SelectedNumber);
			AttemptsCount++;
			if (SelectedNumber > rn)
			{
				printf("Загаданное число меньше. Следующая попытка - ");
			}
			else if (SelectedNumber < rn)
			{
				printf("Загаданное число больше. Следующая попытка - ");
			}
		}
		printf("Поздравляем! Вы угадали! Загаданное число - %d. Количество попыток - %d \n", rn,AttemptsCount);
	}
	if (mode == 2)//второй режим
	{
		printf("Вы загадали число. Оно больше или меньше 500? \n");
		printf("(Подсказка: если число больше, введите знак >, меньше - знак <. Если число угадано, введите =) ");
		scanf_s("%c", &enter);
		scanf_s("%c", &sn);
		AttemptsCount = 1;
		while (sn != '=')
		{
			c1 = c;
			if (sn == '>') 
			{
				mn = c;
				c = (mn + ((mx-mn) / 2));
			}
			else if (sn == '<')
			{
				mx = c;
				c = (mn + ((mx - mn) / 2));
			}
			if (c1 == c)
				break;
			if (c == 0) {
				printf("Вы играли нечестно \n");
				system("pause");
				_Exit(EXIT_SUCCESS);
			}
			AttemptsCount++;
			printf("Ваше число больше или меньше, чем %d? ", c);
			scanf_s("%c", &enter);
			scanf_s("%c", &sn);
		}
		printf("Загаданное число = %d. Количество попыток = %d. \n", c, AttemptsCount);
	}
	system("pause");
}