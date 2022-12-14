#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>



double sin_series(double x, double eps, int nmax, int* add_am) {
    int i;
    double res = 0, x_cur = x;
    for (i = 1; i <= nmax; i++) {
        res += x_cur;
        x_cur *= -x * x / ((2 * i) * (2 * i + 1));
        if (fabs(x_cur) < eps) {
            *add_am = i;
            break;
        }
    }

    if (i == (nmax + 1)) *add_am = nmax;

    return res;
}




double cos_series(double x, double eps, int nmax, int* add_am) {
    int i;
    double res = 0, x_cur = 1;
    for (i = 1; i <= nmax; i++) {
        res += x_cur;
        x_cur *= -x * x / ((2 * i - 1) * (2 * i));
        if (fabs(x_cur) < eps) {
            *add_am = i;
            break;
        }
    }

    if (i == (nmax + 1)) *add_am = nmax;

    return res;
}




double exp_series(double x, double eps, int nmax, int* add_am) {
    int i;
    double res = 0, x_cur = 1;
    for (i = 1; i <= nmax; i++) {
        res += x_cur;
        x_cur *= x / i;
        if (fabs(x_cur) < eps) {
            *add_am = i;
            break;
        }
    }

    if (i == (nmax + 1)) *add_am = nmax;

    return res;
}




double bernoulli(int n)
{
    static double b[100] = { 1, -0.5, 1.0 / 6.0, 0.0 };
    static int len = 3;//number of calculated values

    if (n <= len) return b[n];
    if ((n % 2 && n > 2) || (n >= 100)) return 0;
    double sum = 0;
    double a = -1;
    for (int k = 1; k <= n; ++k)
    {
        a = a * (n - k + 1) / (k + 1);
        sum += a * bernoulli(n - k);
    }
    len += 1;
    b[n] = sum;
    return sum;
}




double ctg_series(double x, double eps, int nmax, int* add_am) {
    int i;
    double res = 0, x_cur = 1, a = 1;
    for (i = 1; i <= nmax; ++i) {
        res += x_cur;
        a *= -2 * x * x / (i * (2 * i - 1));
        x_cur = a * bernoulli(2 * i);
        if (fabs(x_cur) < eps) {
            *add_am = i;
            break;
        }
    }

    if (i == (nmax + 1)) *add_am = nmax;

    return res / x;
}



void wpf(int fnum, int add_am, double x, double eps);
void wps(int fnum, int exp_am, double x);


int main()
{
   int wp, fnum, add_am, exp_am;
   double x, eps;

   printf("Enter work pattern: ");
   scanf_s("%d", &wp);  
   printf("1. sin(x); 2. cos(x); 3.exp(x); 4.ctg(x)\n");
   printf("Enter number of function: ");
   scanf_s("%d", &fnum);
   if ((fnum < 1) || (fnum > 4)) {
       printf("Wrong number of function\n");
       return 0;
    }
   printf("Enter x: ");
   scanf_s("%lf", &x);

   if (wp == 1) {
       printf("Enter eps: ");
       scanf_s("%lf", &eps);
       printf("Enter amount of additives: ");
       scanf_s("%d", &add_am);
       if (add_am <= 0) {
           printf("Wrong number of additives\n");
           return 0;
        }
       wpf(fnum, add_am, x, eps);
    }
   else
       if (wp == 2) {
           printf("Enter amount of experiments: ");
           scanf_s("%d", &exp_am);
           if (exp_am <= 0) {
               printf("Wrong number of experiments\n");
               return 0;
            }
           wps(fnum, exp_am, x);
        }
       else {
           printf("Wrong number of work pattern\n");
           return 0;
        }
   system("pause");
}

void wpf(int fnum, int add_am, double x, double eps) {

    double(*fptr)(double, double, int, int*);
    double(*fptr_c)(double);

    double arg = x;
    int act_add_am = 0;

    switch (fnum)
    {
    case 1:
        fptr = &sin_series;
        fptr_c = sin;
        break;
    case 2:
        fptr = &cos_series;
        fptr_c = cos;
        break;
    case 3:
        fptr = &exp_series;
        fptr_c = exp;
        break;
    case 4:
        fptr = &ctg_series;
        fptr_c = tan;
        arg = M_PI / 2 - x;
        break;
    default:
        printf("Function number is invalid\n");
        return;
    }

    if ((fnum == 4) && (x == 0)) {
        printf("Function is not defined\n");
        return;
    }

    double fc = fptr_c(arg);
    double sf = fptr(x, eps, add_am, &act_add_am);
    printf("C function: %13.10f\n", fc);
    printf("series function: %13.10f\n", sf);
    printf("C function and series function diff: %13.10f\n", fc - sf);
    printf("Amount of additives: %d\n", act_add_am);

    return;
}


void wps(int fnum, int exp_am, double x) {
  
    double eps = 0;

    double(*fptr)(double, double, int, int*);
    double(*fptr_c)(double);

    double arg = x;
    int act_add_am = 0;

    switch (fnum)
    {
    case 1:
        fptr = &sin_series;
        fptr_c = sin;
        break;
    case 2:
        fptr = &cos_series;
        fptr_c = cos;
        break;
    case 3:
        fptr = &exp_series;
        fptr_c = exp;
        break;
    case 4:
        fptr = &ctg_series;
        fptr_c = tan;
        arg = M_PI / 2 - x;
        break;
    default:
        printf("Function number is invalid\n");
        return;
    }

    if ((fnum == 4) && ((x == 0) || (fabs(x) > M_PI))) {
        printf("Function is not defined or series doesnt converge\n");
        return;
    }

    double fc = fptr_c(arg);
    printf("C function: %13.10f\n", fc);

    printf("Add amount  |   Series estimation   |  Diff       \n");
    printf("------------|-----------------------|-------------\n");
    for (int i = 1; i <= exp_am; i++) {
        double sf = fptr(x, eps, i, &act_add_am);
        printf("%12d|%23.8f|%13.10f\n", i, sf, sf - fc);
        printf("------------|-----------------------|-------------\n");
    }

    return;
}





