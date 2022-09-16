#include <stdio.h>
#include <math.h>
void main()
{
	float x1, y1, x2, y2;
	float r1, r2;
	float d;
	printf("Enter in the following order: the coordinates of the center and the radius of the first circle, and then the second");
	scanf_s("%f %f %f %f %f %f", &x1, &y1, &r1, &x2, &y2, &r2);
	d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (d == 0 && r1 == r2) printf("Circles match ");
	else if (d + r1 < r2) printf("Circle overlay ");
	else if (d + r2 < r1) printf("Circle overlay ");
	else if (r2 == d + r1) printf("Inner touch ");
	else if (r1 == d + r2) printf("Inner touch ");
	else if (d == r1 + r2) printf("External touch ");
	else if (r1 + r2 < d) printf("Circles do not have common points ");
	else if (d < r1 + r2) printf("Circles intersect ");
	system("pause");
}