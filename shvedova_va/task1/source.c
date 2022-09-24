#include <stdio.h>
#include <locale.h>
#include <math.h>
void main()
{
	double height, width, depth, thickness_shelf, density_wood, M, m_back, m_side, m_bottom, m_shelves,m_doors;
	int p; //number of shelves inside
	const double density_dsp = 700, density_dvp = 800, thickness_back = 0.005, thickness_side = 0.015, thickness_bottom = 0.015, thickness_door=0.01;
	setlocale(LC_ALL, "Rus");
	printf("enter the height within 180-220 cm: ");
	scanf_s("%lf", &height);
	printf("enter the width within 80-120 cm: ");
	scanf_s("%lf", &width);
	printf("enter the depth within 50-90 cm: ");
	scanf_s("%lf", &depth);
	printf("enter the density of the wood (kg/m^3): ");
	scanf_s("%lf", &density_wood);
	printf("enter the thickness of shelves 5-15 mm: ");
	scanf_s("%lf", &thickness_shelf);
	if ((height >= 180) && (height <= 220) && (width >= 80) && (width <= 120) && (depth >= 50) && (depth <= 90) && (thickness_shelf >= 5) && (thickness_shelf <= 15))
	{
		p = height / 40;
		height = height / 100; //meters
		width = width / 100; //meters
		depth = depth / 100; //meters
		thickness_shelf = thickness_shelf / 1000; //meters
		m_back = thickness_back * height * width * density_dvp; 
		m_side = thickness_side * height * depth * density_dsp; 
		m_bottom = thickness_bottom * width * depth * density_dsp; 
		m_shelves = thickness_shelf * depth * (width - 2 * thickness_side) * density_dsp; 
		m_doors = thickness_door * height * width * density_wood; 
		M = m_back + 2 * m_side + 2 * m_bottom + p * m_shelves + m_doors;
		printf("The mass is  %lf ", M);
	}
	else 
		printf("Invalid values entered, try again! ");
	system("pause");
}