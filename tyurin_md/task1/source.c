#include <stdio.h>
#include <math.h>

void main() {
	double h, w, d, weight_1, weight_2, weight_3, weight_4, weight_5, all_weight;
	int cnt_shelves;
	// density of materials(kg/cm^3)
	const double density_DSP = 0.00065, density_DVP = 0.00075, density_wood = 0.00055;
	// thickness of parts(cm)
	const double thickness_1 = 0.5, thickness_2 = 1.5, thickness_3 = 1.5, thickness_4 = 1;
	// distance between the shelves
	const int distance_between_the_shelves = 40;
	// enter 
	printf("Enter the values h, w, d in centimeters\n");
	scanf_s("%lf %lf %lf", &h, &w, &d);

	// calculations
	if ((h >= 180) & (h <= 220) & (w >= 80) & (w <= 120) & (d >= 50) & (d <= 90)) {   // check h, w, d
		weight_1 = ((h * w * thickness_1) * density_DVP);
		weight_2 = (((h * d * thickness_2) * density_DSP) * 2);
		weight_3 = (((w * d * thickness_3) * density_DSP) * 2);
		weight_4 = ((h * w * thickness_4) * density_wood);
		cnt_shelves = (h / (distance_between_the_shelves + thickness_2));
		weight_5 = (((w * d * thickness_3) * density_DSP) * cnt_shelves);
		all_weight = (weight_1 + weight_2 + weight_3 + weight_4 + weight_5);
		printf("Number of shelves = % d\n", cnt_shelves);
		printf("Wardrobe weight in kilograms = %lf\n", all_weight);
	}
	else {
		printf("You are entering incorrect data!\n");
	}
	system("PAUSE");
}








