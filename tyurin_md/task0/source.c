#include <stdio.h>
#include <math.h>
void main() {
	//variable declaration
	double x1, y1, x2, y2, r1, r2;
	double d;
	//enter
	printf("Enter the coordinates and radius of the biggest circle ");
	scanf_s("%lf %lf %lf", &x1, &y1, &r1);
	printf("Enter the coordinates and radius of the second circle ");
	scanf_s("%lf %lf %lf", &x2, &y2, &r2);
	//distance
	d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	//radius
	r1 = fabs(r1);
	r2 = fabs(r2);

	if (r1 >= r2) { //check radius
		if ((d == 0) && (r1 == r2)) {
			printf("8\n");
		}
		else if ((d > r1 + r2) || (d < r1 - r2)) {
			printf("0\n");
		}
		else if ((d == r1 + r2) || (d == r1 - r2)) {
			printf("1\n");
		}
		else { printf("2\n"); }
	}
	else { printf("You enter wrong radius!"); }
}









