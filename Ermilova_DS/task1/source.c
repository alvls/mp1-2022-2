#include <stdio.h>

int main()
{
	double h, w, d, mass, t1, t2, t3, back_wall, side_walls, lids, doors, shelves;
	int cnt, p1, p2, p3;
	t1 = 0.005; // t1, t2, t3 - thickness in meters
	t2 = 0.015;
	t3 = 0.01;
	p1 = 800; // approximate density of wood chipboard (kg/m2)
	p2 = 820; // approximate density of fiberboard (kg/m2)
	p3 = 600; // approximate density of wood (kg/m2)
	printf("enter the wardrobe size (height, width and depth (in meters))");
	scanf_s("%lf %lf %lf", &h, &w, &d);
	if ((h > 1.8) && (h < 2.2) && (w > 0.8) && (w < 1.2) && (d > 0.5) && (d < 0.9)) {
		cnt = (h / 0.4); // amount of shelves
		back_wall = h * w * t1; // volumes of details
		side_walls = 2 * h * d * t2;
		lids = 2 * w * d * t2;
		doors = 2 * h * w * t3;
		shelves = cnt * d * w * t2;
		mass = (back_wall * p2) + (side_walls * p1) + (lids * p1) + (doors * p3) + (shelves * p1);
		printf("wardrobe mass -  %lf", mass);
	}
	else {
		printf("Wrong data");
	}
	system("pause");
}










