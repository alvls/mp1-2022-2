#include <stdio.h>
#include <stdlib.h>

// Generating a random number within a given range
int random_number(int start, int end)
{
	return rand() % ((end - start) + 1) + start;
}

void main()
{
	char who_guesses;
	printf("Who will guess the number?\nIf user, enter 'u', if computer machine, enter 'm': ");
	who_guesses = getch();

	int original_value, guessed_value;
	int count_of_attemps = 0;
	srand(time(NULL));

	if (who_guesses == 'u')
	{
		const int start = 0, end = 1000;
		original_value = random_number(start, end);
		do
		{
			count_of_attemps++;
			printf("\nWhat is your guess? (int number from 1 to 1000): ");
			scanf_s("%d", &guessed_value);

			if ((guessed_value < 1) || (guessed_value > 1000))
				printf("Maybe you should try entering a number between 1 and 1000? :)\n");

			else if (guessed_value == original_value)
				printf("\nYou win! Your count of attepms: %d.\n", count_of_attemps);

			else if (guessed_value < original_value)
				printf("The entered value is less then the original value. Try again!\n");

			else
				printf("The entered value is greater then the original value. Try again!\n");
		}
		while (guessed_value != original_value);
	}
	else if (who_guesses == 'm')
	{
		char condition;
		int start = 0, end = 1000;
		printf("\nEnter the original value (int number from 1 to 1000): ");
		scanf_s("%d", &original_value);
		do
		{
			count_of_attemps++;
			guessed_value = random_number(start, end);
			printf("\nIs it %d? (enter '<', '>' or '=')\n", guessed_value);
			condition = getch();

			if ((condition != '<') && (condition != '>') && (condition != '='))
			{
				printf("\nYou entered an invalid value. Game over!\n");
				break;
			}

			// We narrow the boundaries of number generation according to the available information
			else if (condition == '=')
				printf("That is all! Number of computer attemps: %d.\n", count_of_attemps);

			else if (condition == '<')
				end = guessed_value;

			else
				start = guessed_value;
			
		}
		while (condition != '=');
	}
	else
		printf("\n\nYou entered an invalid value!\n\n");

	system("pause");
}