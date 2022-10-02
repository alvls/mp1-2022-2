#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
void main()

{
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int mode;
	printf("Enter mode number (1 or 2):");
	scanf_s("%d", &mode);
	if (mode == 1) {
		int cnt = 1;
		int a = 0; //The number you are guessing
		int number = ("%d\n", 1 + rand() % 1000);
		while (a != number) {
			printf("Guess the number\n");
			scanf_s("%d", &a);
			if (a > number) {
				printf("The hidden number is less\n");
				cnt += 1;
			}
			else if (a < number) {
				printf("The hidden number is greater\n");
				cnt += 1;
			}
			else {
				printf("You guessed it! Number of tries: %d\n", cnt);
			}
			system("pause");
		}
	}
	else if (mode == 2) {
		int a, number, cnt, start, end, win;
		char sign;
		cnt = 1;
		start = 1;
		end = 1000;
		a = 0;
		win = 0;
		printf("Enter a number from 1 to 1000\n");
		scanf_s("%d", &number);
		while (win != 1) {
			int a = rand() % ((end - start) + 1) + start;
			printf("You guessed the number %d\n", a);
			printf("Enter sign (> < =):");
			scanf_s(" %c", &sign);
			if (sign == '>') {
				cnt++;
				start = a;
			}
			else if (sign == '<') {
				cnt++;
				end = a;
			}
			else if (sign == '=') {
				win = 1;
				printf("You guessed it! Number of tries:: %d", cnt);
			}
		}
		system("pause");
	}
}
