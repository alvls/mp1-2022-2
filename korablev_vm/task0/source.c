#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <windows.h>
void main()
{
    //задаем переменные + локализация
    char* locale = setlocale(LC_ALL, "Rus");
    int x1, y1, x2, y2, r1, r2;
    int distance, R, r; //расстояние между центрами, больший и меньший радиус
    //
    //ввод данных
    printf("x1 and y1 are the coordinates of the center of the 1st circle, x2 and y2 are the coordinates of the center of the 2nd circle, r1 and r2 are the radii of the 1st and 2nd circles, respectively\n");
    printf("Enter x1,y1,x2,y2,r1,r2 in the appropriate order ");
    scanf("%d,%d,%d,%d,%d,%d", &x1, &y1, &x2, &y2, &r1, &r2);
    //
    //настройка переменных
    distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    if (r1 > r2)
    {
        R = r1;
        r = r2;
    }
    else
    {
        R = r2;
        r = r1;
    }
    //
    //логические преобразования
    if (distance > (R + r))
    {
        printf("The circles do not intersect, they lie separately from each other\n"); //Окружности не пересекаются, лежат отдельно друг от друга
    }
    else if ((distance == 0) && (R == r))
    {
        printf("The circles lie on top of each other\n"); //Окружности совпадают 
    }
    else if ((distance == (R + r)) && (distance > 0))
    {
        printf("The circles lie separately from each other, have 1 intersection point\n"); //Окружности лежат отдельно друг от друга, имеют 1 точку пересечения
    }
    else if (distance < (R - r))
    {
        printf("One circle lies inside the other, do not intersect\n"); //Одна окружность лежит внутри другой, не пересекаются
    }
    else if (distance == (R - r))
    {
        printf("One circle lies inside the other, have 1 intersection point\n"); //Одна окружность лежит внутри другой, 1 пересечение
    }
    else if (((R - r) < distance) && (distance < (R + r)))
    {
        printf("The circles intersect at two points\n"); //Окружности пересекаются в двух точках
    }
    else
    {
        wprintf("Fail\n"); //Ошибка
    }
    system("pause");
}