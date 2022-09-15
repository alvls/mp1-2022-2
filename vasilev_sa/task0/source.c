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

void main()
{
    int x1, y1, r1, x2, y2, r2, rmax, rmin;
    double ditance;
    printf("Enter the coordinates and radius of the first circle ");
    scanf_s("%d %d %d", &x1, &y1, &r1);
    printf("Enter the coordinates and radius of the second circle ");
    scanf_s("%d %d %d", &x2, &y2, &r2);
    rmax = findMax(r1, r2);
    rmin = findMin(r1, r2);
    ditance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    if ((ditance > rmax + rmin) || (ditance + rmin < rmax))
    {
        printf("0 crossings\n");
    }
    else if ((ditance == 0) && (rmax == rmin))
    {
        printf("Conside\n");
    }
    else if ((ditance == rmax + rmin) || (ditance + rmin == rmax))
    {
        printf("1 crossing\n");
    }
    else
    {
        printf("2 crossings\n");
    }
    system("pause");
}