#include <stdio.h>
#include <math.h>

// Input validation function (h, w, d)
int data_validation(float h, float w, float d)
{
	if ((h < 180) || (h > 220) || (w < 80) || (w > 120) || (d < 50) || (d > 90))
		return 0;

	else
		return 1;
}

void main()
{
	// Dimensions of furniture parts (in centimeters)
	const float fibreboard_thickness = 0.05;
	const float chipboard_thickness = 0.15;
	const float wood_door_thickness = 0.01;


	// Approximate material densities (g/cm^3)
	const float fibreboard_density = 0.8;
	const float chipboard_density = 0.75;
	const float wood_density = 0.7;


	// Distance between shelves
	const int distance_between_shelves = 40;


	float h, w, d;


	printf("Enter the values h, w, d (in centimeters): ");
	scanf_s("%f %f %f", &h, &w, &d);

	int validation_result = data_validation(h, w, d);

	if (validation_result)
	{
		// Let's find the masses of different parts

		float back_wall_mass = ((h * w * fibreboard_thickness) * fibreboard_density) * 0.001;

		float sidewall_mass = ((h * d * chipboard_thickness) * chipboard_density) * 0.001;

		float cover_mass = ((w * d * chipboard_thickness) * chipboard_density) * 0.001;

		float door_mass = ((h * (w / 2) * wood_door_thickness) * wood_density) * 0.001;

		// The thickness of the side walls can be neglected
		float shelf_mass = ((w * d * chipboard_thickness) * chipboard_density) * 0.001;


		// Now let's find the number of shelves
		int number_of_shelves = h / (distance_between_shelves + chipboard_thickness);


		// Finally, let's determine the total mass
		float total_mass = back_wall_mass + (sidewall_mass * 2) + (cover_mass * 2) + (door_mass * 2) + (shelf_mass * number_of_shelves);

		int approximate_total_mass = roundf(total_mass);

		printf("Approximate wardrobe mass: %d kg.\nMore accurate value: %f kg.\n", approximate_total_mass, total_mass);
	}

	else
		printf("The entered data is not in the correct format.\n");
	
	system("pause");
}





