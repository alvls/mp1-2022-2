#include<stdio.h>
#include<math.h>
void main()
{
	double x1, x2, y1, y2, r1, r2;
	double dist;
	printf(" VVEDITE x1,y1,x2,y2,r1,r2, gde r1 > r2");
	scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &r1, &r2);
	dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	if (dist > r1 + r2)
		printf("ne peresekautcia");
	else if (dist < r1 - r2)
		printf("odna vnutri drugoi,tochek kasania net");
	else if (dist = r1 - r2)
		printf("odna vnutri drugoi, vnutrennee kasanie");
	else if (dist = r1 + r2)
		printf("vneshnee kasanie");
	else if ((dist < r1 + r2) && (dist > r1 - r2))
		printf("Dve tochki peresecheniya");
	else if (dist = 0)
		printf("krugi nalojeni drug na druga");
	system("pause");
}
