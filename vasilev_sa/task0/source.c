#include <stdio.h>
#include <math.h>
#include <locale.h>

int findMax(int x, int y) 
{
    return (x > y) ? x : y;
}

int findMin(int x, int y)
{
    return (x < y) ? x : y;
}

void main()
{   
    setlocale(LC_ALL, "Russian");
    int x1, y1, r1, x2, y2, r2, rmax, rmin;
    double distance;
    printf("¬ведите радиус первой окружности ");
    scanf_s("%d %d %d", &x1, &y1, &r1);
    printf("¬ведите радиус второй окружности ");
    scanf_s("%d %d %d", &x2, &y2, &r2);
    rmax = findMax(r1, r2);
    rmin = findMin(r1, r2);
    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    if ((distance > rmax + rmin) || (distance < rmax - rmin)) printf("0 пересечений\n");
    else if ((distance == 0) && (rmax == rmin)) printf("ќкружности совпадают\n");
    else if ((distance == rmax + rmin) || (distance == rmax - rmin)) printf("1 пересечение\n");
    else printf("2 пересечени€\n");
    system("pause");
}