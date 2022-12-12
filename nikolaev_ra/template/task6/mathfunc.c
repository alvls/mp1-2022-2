#include "main.h"
#include "mathfunc.h"

// Arrays of function pointers for calling standard functions and calculating a specific term for the specified function
double (*built_in_functions [COUNT_OF_FUNCTIONS]) (double                      ) = { sin,                   cos,                     exp,                       cosh                               };
double (*calculation_step   [COUNT_OF_FUNCTIONS]) (double x, int current_number) = { sine_calculation_step, cosine_calculation_step, exponent_calculation_step, hyperbolic_cosine_calculation_step };

// Factorial calculation
double factorial(int n)
{
	double result = 1;
	for (int i = 2; i <= n; i++)
		result *= i;
	return result;
}

// Calculation of a specific term for the sine function.
double sine_calculation_step(double x, int current_number)
{
	return pow(-1, current_number) * pow(x, 2 * current_number + 1) / factorial(2 * current_number + 1);
}

// Calculation of a specific term for the cosine function.
double cosine_calculation_step(double x, int current_number)
{
	return pow(-1, current_number) * pow(x, 2 * current_number) / factorial(2 * current_number);
}

// Calculation of a specific term for the exponential function.
double exponent_calculation_step(double x, int current_number)
{
	return pow(x, current_number) / factorial(current_number);
}

// Calculation of a specific term for the hyperbolic cosine function.
double hyperbolic_cosine_calculation_step(double x, int current_number)
{
	return pow(x, 2 * current_number) / factorial(2 * current_number);
}

// Implementation of a single calculation of the function value
void math_single_calculation(double x, double accuracy, int n, int number_of_function)
{
	double result = 0;
	double reference = built_in_functions[number_of_function](x);
	int i;
	for (i = 0; i < n && fabs(reference - result) > accuracy; i++)
		result += calculation_step[number_of_function](x, i);
	system("cls");
	printf("Reference value: %lf\n", reference);
	printf("Calculated function value: %lf\n", result);
	printf("Difference between calculated and reference value: %lf\n", fabs(reference - result));
	printf("Count of terms: %d\n", i);
}

// Implementation of serial experiment
void math_serial_experiment(double x, int n, int number_of_function)
{
	double result = 0;
	double reference = built_in_functions[number_of_function](x);
	int i;
	system("cls");
	printf("Reference value: %lf\n\n", reference);
	printf("TERMS                    EXPERIMENTAL VALUE                        DIFFERENCE\n");
	printf("-----                    ------------------                    ------------------\n");
	for (i = 0; i < n; i++)
	{
		result += calculation_step[number_of_function](x, i);
		printf("%5.2d                    %18.6lf                    %18.6lf\n", i + 1, result, fabs(reference - result));
	}
}