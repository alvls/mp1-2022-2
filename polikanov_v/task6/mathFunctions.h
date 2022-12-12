long double taylorSin(long double x, long double acc, int num_of_row_elem, int mode, int experiments);
long double taylorCos(long double x, long double acc, int num_of_row_elem, int mode, int experiments);
long double taylorExp(long double x, long double acc, int num_of_row_elem, int mode, int experiments);
long double taylorCoth(long double x, long double acc, int num_of_row_elem, int mode, int experiments);
typedef long double (*mathFunc) (long double, long double, int, int, int);