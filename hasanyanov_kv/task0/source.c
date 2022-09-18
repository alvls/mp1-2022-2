#include <stdio.h>
#include <locale.h>
#include <math.h>

int main()
{
    setlocale(LC_ALL, "Russian");

    double x1, x2, y1, y2, r1, r2, d = 0;
    printf("Задайте параметры первой окружности (x1, y1, r1)\n");
    if (scanf_s("%lf %lf %lf", &x1, &y1, &r1) != 3 || r1 <= 0)
    {
        printf("Неверные данные\n");
        return 1;
    }
    printf("Задайте параметры второй окружности (x2, y2, r2\n");
    if (scanf_s("%lf %lf %lf", &x2, &y2, &r2) != 3 || r2 <= 0)
    {
        printf("Неверные данные\n");
        return 1;
    }
    d = sqrt(x2 * x2 - 2 * x2 * x1 + x1 * x1 + y2 * y2 - 2 * y1 * y2 + y1 * y1);

    if (r1 == r2 && d == 0)
        printf("Окружности совпадают\n");
    else if (d < fabs(r1 - r2) && d > 0)
        printf("Вторая окружность лежит в первой\n");
    else if (d == fabs(r1 - r2))
        printf("Окружности касаются внутренним образом (одна общая точка)\n");
    else if (d > fabs(r1 - r2) && d < (r1 + r2))
        printf("Окружности пересекаются (две общие точки)\n");
    else if (d == (r1 + r2))
        printf("Окружности касаются внешним образом (одна общая точка)\n");
    else if (d > (r1 + r2))
        printf("Окружности не касаются\n");

    system("PAUSE");
    return 0;
}
