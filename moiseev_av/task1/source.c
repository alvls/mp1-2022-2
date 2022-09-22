#include <math.h>
#include <stdio.h>
#include <locale.h>

void main()
{
	setlocale(LC_ALL, "Rus");
	float thickness_of_back_wall, thickness_of_side_wall, thickness_of_upper_and_lower_wall, thickness_of_doors, thickness_of_shelf; //переменные для ширины
	float p1, p2, p3, mass;
	float v1, v2, v3, v4, v5;
	int h, w, depth, num_shelf;
	
	p1 = 800;
	p2 = 450;
	p3 = 540;
	thickness_of_back_wall = 0.05;
	thickness_of_side_wall = 0.15;
	thickness_of_upper_and_lower_wall = 0.15;
	thickness_of_doors = 1;
	thickness_of_shelf = 1;

	printf("Введите высоту задней стенки в сантиметрах: ");
	scanf_s("%d", &h);
	if ((h < 180) || (h >= 220))
	{
		printf("Введена не допустимая высота!");
	}
	else
	{
		printf("Введите ширину задней стенки в сантиметрах: ");
		scanf_s("%d", &w);
		if ((w < 80) || (w >= 120))
		{
			printf("Введена не допустимая ширина!");
		}
		else
		{
			printf("Введите глубину шкафа в сантиметрах: ");
			scanf_s("%d", &depth);
			if ((depth < 50) || (depth > 90))
			{
				printf("Введена не допустимая глубина!");
			}
			else
			{
				if (h % 40 == 0)
				{
					num_shelf = h / 40 - 1;
				}
				else
				{
					num_shelf = h / 40;
				}
				v1 = h * w * thickness_of_back_wall;
				v2 = 2 * h * depth * thickness_of_side_wall;
				v3 = 2 * w * depth * thickness_of_upper_and_lower_wall;
				v4 = 2 * h * w * thickness_of_doors;
				v5 = num_shelf * thickness_of_shelf * w * depth;
				mass = (p1 * v1 + p2 * (v2 + v3 + v5) + p3 * v4) * 0.000001;
				printf("Масса шкафа: %f", mass);
			}
		}
	}
}
