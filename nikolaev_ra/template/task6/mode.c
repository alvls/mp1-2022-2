#include "main.h"
#include "mode.h"
#include "addfunc.h"
#include "mathfunc.h"
#include "navigation.h"

// Common part of both modes of operation
void operating_mode()
{
	system("cls");
	int number_of_function = 0, x = 0, accuracy = 0, n = 0;
	do
	{
		printf("Choose a function to calculate the value:\n\n");
		printf("0 - sine (sin x)\n");
		printf("1 - cosine (cos x)\n");
		printf("2 - exponent (exp x)\n");
		printf("3 - hyperbolic cosine (cosh x)\n");
		printf("\nSelect one of the items: ");
		scanf_s("%d", &number_of_function);
		clean_stdin();
		if (number_of_function != 0 && number_of_function != 1 && number_of_function != 2 && number_of_function != 3)
			printf("\nAnd what did you mean by that?\nCheck the entered data and try again!\n");

	} while (number_of_function != 0 && number_of_function != 1 && number_of_function != 2 && number_of_function != 3);

	system("cls");
	printf("Now enter the value of the point where you want to calculate the value (in radians): ");
	scanf_s("%d", &x);
	clean_stdin();
	system("cls");

	// The first mode - up to 1000, the second - up to 25
	// The variable 'mode' from the navigaion.h file is used
	if (mode == '1')
	{
		do
		{
			printf("Enter the number of terms (1 - 1000): ");
			scanf_s("%d", &n);
			clean_stdin();
			if (n < MIN_N_VALUE || n > MAX_N_VALUE_SINGLE_CALCULATION)
				printf("\nCheck the entered data and try again!\n\n");
		} while (n < MIN_N_VALUE || n > MAX_N_VALUE_SINGLE_CALCULATION);
		single_calculation(x, n, number_of_function);
	}
	else
	{
		do
		{
			printf("Enter the number of terms (1 - 25): ");
			scanf_s("%d", &n);
			clean_stdin();
			if (n < MIN_N_VALUE || n > MAX_N_VALUE_SERIAL_EXPERIMENT)
				printf("\nCheck the entered data and try again!\n\n");
		} while (n < MIN_N_VALUE || n > MAX_N_VALUE_SERIAL_EXPERIMENT);
		serial_experiment(x, n, number_of_function);
	}
}

// Procedure for additional data (required only for this mode) and switching to work with the single calculation mode
void single_calculation(int x, int n, int number_of_function)
{
	system("cls");
	double accuracy = 0.0;
	do
	{
		printf("Enter an accuracy of calculation (>= 0.000001): ");
		scanf("%lf", &accuracy);
		clean_stdin();
		if (accuracy < MIN_ACCURACY_VALUE)
			printf("\nCheck the entered data and try again!\n\n");
	} while (accuracy < MIN_ACCURACY_VALUE);
	system("cls");

	math_single_calculation(x, accuracy, n, number_of_function);
}

// Procedure for switching to work with the serial experiment mode (to enter additional data for this mode in the future if it will be necessary)
void serial_experiment(int x, int n, int number_of_function)
{
	math_serial_experiment(x, n, number_of_function);
}