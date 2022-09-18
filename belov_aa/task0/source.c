#include <stdio.h>
#include <math.h>

void main()
{
	int distance, x1, x2, y1, y2, r1, r2;
	printf("Input coordinates of the center of the circles and their radius: x1 and x2, then y1 and y2, then r1 and r2");
	scanf_s("%d%d%d%d%d%d", &x1, &x2, &y1, &y2, &r1, &r2);
	distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	if (distance > r1 + r2)
		printf("The circles do not intersect\n");
	else if (distance < r1 - r2)
		printf("One circle is inside the other and they have no common points\n");
	else if (distance = r1 - r2)
		printf("One circle is inside the other and they have a common point\n");
	else if (r1 - r2 < distance < r1 + r2)
		printf("The circles intersect and have two points in common\n");
	else if (distance = r1 + r2)
		printf("The circles donot intersect and have one common point\n");
	else if (distance = 0)
		printf("The circles are at the same point\n");
	system("PAUSE");
}