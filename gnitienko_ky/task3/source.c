#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define ENUM 11

void main()
{
	setlocale(LC_ALL, "Rus");

	int n = 0;
	while (1) {
		printf("Enter the length of the guessed number n (from 2 to 5): ");
		scanf_s("%i", &n);
		if (n > 5 || n < 2) {
			printf("Wrong length, try again\n\n\n");
		}
		else
			break;
	}

	int number = 0, digit, count_of_try = 0, surrender = 0;
	int digits[] = { 0,1,2,3,4,5,6,7,8,9 }, bot_mas[5] = { 0 }, user_mas[5] = { 0 };
	for (int i = 0; i < n; i++) {
		srand(time(0));
	again:
		digit = rand() % 10;
		if (digits[digit] < 10) {
			if ((i == 0) && (digit == 0)) {
				bot_mas[i] = 1;
				digits[1] = ENUM;
			}
			else {
				bot_mas[i] = digits[digit];
				digits[digit] = ENUM;
			}
		}
		else
			goto again;
		//printf("%d", bot_mas[i]);
	}
	printf("\n");
	/// 
	/// 
	printf("\nTry to guess the number\n");
retry:
	int guess, guess1, digit_of_number;
	int i = n - 1;
	scanf_s("%i", &guess1);
	guess = guess1;
	while ((i >= 0) && (guess != 0)) {
		digit_of_number = guess % 10;
		user_mas[i] = digit_of_number;
		guess /= 10;
		i--;
	}
	//for (int i = 0; i < n; i++)  //Проверить пользовательский массив
		//printf("%i", user_mas[i]);

	int bulls = 0, cows = 0;
	for (i = 0; i < n; i++) {
		if (bot_mas[i] == user_mas[i])
			bulls++;
		else for (int j = 0; j < n; j++)
			if (user_mas[i] == bot_mas[j])
				cows++;
	}
	// ВЫВОД:

	int is_win = 1;
	for (int i = 0; i < n; i++)
		if (bot_mas[i] != user_mas[i]) {
			is_win = 0;
			count_of_try++;
			if (bulls == 1 && cows == 0) {
				printf("A bull in your number\n"); break;
			}
			else if (bulls == 0 && cows == 1) {
				printf("A cow in your number\n"); break;
			}
			else if (bulls <= n && cows == 0) {
				printf("In your number %i bulls\n", bulls); break;
			}
			else if (cows <= n && bulls == 0) {
				printf("In your number %d cows\n", cows); break;
			}
			else if (bulls > 1 && cows > 1) {
				printf("In your number %i bulls and %d cows\n", bulls, cows); break;
			}
			else if (bulls == 1 && cows == 1) {
				printf("In your number %i bull and %d cow\n", bulls, cows); break;
			}
			else if (bulls > 1 && cows == 1) {
				printf("In your number %i bulls and %d cow\n", bulls, cows); break;
			}
			else if (bulls == 1 && cows > 1) {
				printf("In your number %i bull and %d cows\n", bulls, cows); break;
			}
			else {
				printf("In your number no bulls and no cows\n"); break;
			}
		}
	if (count_of_try == 5 || count_of_try == 10 || count_of_try == 15) {
		printf("Do you want to surrender? (1 - yes, 2 - no) ");
		scanf_s("%i", &surrender);
		if (surrender == 1) {
			printf("You lose. Hidden number is - ");
			for (int i = 0; i < n; i++) printf("%i", bot_mas[i]);
			printf("\n");
			system("pause");
			return;
		}
		if (surrender == 2)
			goto retry;
	}
	if (!is_win)
		goto retry;
	else printf("You won! Your answer is %d\n", guess1);
	system("pause");
	return;
}