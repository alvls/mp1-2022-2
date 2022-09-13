#include <stdio.h>
#include <math.h>
void main()
{
    int x1, y1, r1, x2, y2, r2, rmax, rmin;
    double ditance;
    printf("Enter the coordinates and radius of the first circle ");
    scanf_s("%d %d %d", &x1, &y1, &r1);
    printf("Enter the coordinates and radius of the second circle ");
    scanf_s("%d %d %d", &x2, &y2, &r2);
    if (r1 > r2)
    {
        rmax = r1;
        rmin = r2;
    }
    else
    {
        rmax = r2;
        rmin = r1;
    }
    ditance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    if ((ditance > rmax + rmin) || (ditance + rmin < rmax))
    {
        printf("0 crossings\n");
    }
    else
    {
        if ((ditance == 0) && (r1 == r2))
        {
            printf("Сoincide\n");
        }
        else
        {
            if ((ditance == rmax + rmin) || (ditance + rmin == rmax))
            {
                printf("1 crossing\n");
            }
            else
            {
                printf("2 crossings\n");
            }
        }
    }
    system("pause");
}

