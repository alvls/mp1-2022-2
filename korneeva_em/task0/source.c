#include <math.h>
#include <stdio.h>
void main()
{
	float x1, y1, R1, x2, y2, R2;
	float l;
	printf("Input the coordinates and radius of the first circle first, then the second:");
	scanf("%f %f %f %f %f %f", &x1, &y1, &R1, &x2, &y2, &R2);
	l = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
	if ((l == 0) && (R1 == R2))
		printf("the circles match");
	if (l > (R1 + R2))
		printf("the circles do not intersect");
	else if (abs(l - (R1 + R2)) == 0)
		printf("touching circles");
	else if (l < (R1 + R2)) {
		if (l > (R1 - R2))
			printf("intersecting circles");
		else printf("a circle inside another");
	}

}






