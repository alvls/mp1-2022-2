#include<math.h>
#include<stdio.h>
#include<locale.h>
void main() {
	double h, d, w, m1, m2, m3, m4, m5, k;
	double l,j;
	double thickness_back_wall, top_and_bottom_cover_thicknes, side_walls_thicknes, overhead_doors_thicknes, densityDSP, densityDVP, densityWOOD;
	setlocale(LC_ALL, "RUS");
	k = 1000;
	thickness_back_wall = 5;
	top_and_bottom_cover_thicknes = 15;
	side_walls_thicknes = 15;
	overhead_doors_thicknes = 10;
	densityDSP = 0.00055;
	densityDVP = 0.00085;
	densityWOOD = 0.00072;
	printf("¬ведите: высоту h в мм (1800 - 2200), глубину d в мм(500 - 900), ширину w в мм(800 - 1200)");
	scanf("%lf%lf%lf", &h, &d, &w);
	m1 = (h * w * thickness_back_wall) * densityDVP;
	m2 = ((h * d * side_walls_thicknes) * densityDSP) * 2;
	m3 = ((w * d * top_and_bottom_cover_thicknes) * densityDSP) * 2;
	m4 = ((h * w * overhead_doors_thicknes) * densityWOOD);
	if (h <= 2000)
		j = 4;
	else if (h > 2000)
		j = 5;
	m5 = w * d * j * side_walls_thicknes * densityDSP;
	l = (m1 + m2 + m3 + m4 +m5) / k;
	printf("масса(кг) = %lf", l);
	system("pause");
}

