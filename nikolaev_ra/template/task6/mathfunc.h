#ifndef MATHFUNC_H
#define MATHFUNC_H

#define COUNT_OF_FUNCTIONS 4

double factorial(int n);

double sine_calculation_step(double x, int current_number);
double cosine_calculation_step(double x, int current_number);
double exponent_calculation_step(double x, int current_number);
double hyperbolic_cosine_calculation_step(double x, int current_number);

void math_single_calculation(double x, double accuracy, int n, int number_of_function);
void math_serial_experiment(double x, int n, int number_of_function);

#endif // !MATHFUNC_H

