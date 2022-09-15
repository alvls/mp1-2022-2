#include <stdio.h>
#include <math.h>

int findMax(int x, int y) 
{
    return (x > y) ? x : y;
}

int findMin(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    int x1, y1, r1, x2, y2, r2, rmax, rmin;
    double distance;
    printf("Enter the coordinates and radius of the first circle ");
    scanf_s("%d %d %d", &x1, &y1, &r1);
    printf("Enter the coordinates and radius of the second circle ");
    scanf_s("%d %d %d", &x2, &y2, &r2);
    rmax = findMax(r1, r2);
    rmin = findMin(r1, r2);
    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    if ((distance > rmax + rmin) || (distance < rmax - rmin))
    {
        printf("0 crossings\n");
    }
    else if ((distance == 0) && (rmax == rmin))
    {
        printf("Conside\n");
    }
    else if ((distance == rmax + rmin) || (distance == rmax - rmin))
    {
        printf("1 crossing\n");
    }
    else
    {
        printf("2 crossings\n");
    }
    system("pause");
    return 0;
}