#ifndef MODE_H
#define MODE_H

#define MIN_N_VALUE                     1
#define MAX_N_VALUE_SINGLE_CALCULATION  1000
#define MAX_N_VALUE_SERIAL_EXPERIMENT   25
#define MIN_ACCURACY_VALUE              0.000001                        

void operating_mode();
void single_calculation(int x, int n, int number_of_function);
void serial_experiment(int x, int n, int number_of_function);

#endif // !MODE_H
