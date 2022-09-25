#include <stdio.h>
#include <math.h>
void main()
{
	double r1, x1, y1, r2, x2, y2, distance;
	printf("Enter radius and center coordinates for 2 circles: ");
	scanf_s("%lf %lf %lf %lf %lf %lf", &r1, &x1, &y1, &r2, &x2, &y2);
	distance = abs(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
	if ((r1 == r2) && (x1 == x2) && (y1 == y2)) {
		printf("circles coincide");
	}
	else if (distance == (r1 + r2)) {
		printf("circles touch at 1 point");
	}
	else if (distance > (r1 + r2)) {
		printf("circles do not touch");
	}
	else if (distance == (abs(r1 - r2))) {
		printf("circle lies inside another and touches it");
	}
	else if (distance < (abs(r1 - r2))) {
		printf("circle lies inside the other and does not touch it");
	}
	else if ((abs(r1 - r2)) < distance < r1 + r2) {
		printf("circles touch at 2 points");
	}
	system("pause");
}