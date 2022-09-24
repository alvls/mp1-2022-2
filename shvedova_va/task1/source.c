#include <stdio.h>
#include <locale.h>
#include <math.h>
void main()
{
	double height, width, depth, thickness_inside, density_wood, M, m_back, m_side, m_bottom, m_inside,m_doors;
	int p; //количесво внутренних полок
	const double density_dsp = 700, density_dvp = 800, thickness_back = 0.005, thickness_side = 0.015, thickness_bottom = 0.015, thickness_door=0.01;
	setlocale(LC_ALL, "Russian");
	printf("введите высоту шкафа в пределах 180-220 см: ");
	scanf_s("%lf", &height);
	printf("введите ширину шкафа в пределах 80-120 см: ");
	scanf_s("%lf", &width);
	printf("введите глубину шкафа в пределах 50-90 см: ");
	scanf_s("%lf", &depth);
	printf("введите плотность используемого дерева в кг/м^3: ");
	scanf_s("%lf", &density_wood);
	printf("введите толщину внутренних полок в пределах 5-15 мм: ");
	scanf_s("%lf", &thickness_inside);
	p = height / 40;
	height = height / 100; //высота в метрах
	width = width / 100; //ширина в метрах
	depth = depth / 100; //глубина в метрах
	thickness_inside = thickness_inside / 1000; //толщина внутренних полок в метрах
	m_back = thickness_back * height * width * density_dvp; //масса задней стенки
	m_side = thickness_side * height * depth * density_dsp; //масса боковины
	m_bottom = thickness_bottom * width * depth * density_dsp; //масса нижней/верхней крышки
	m_inside = thickness_inside * depth * (width - 2 * thickness_side) * density_dsp; //масса внутренней полки
	m_doors = thickness_door * height * width * density_wood; //масса дверей
	M = m_back + 2 * m_side + 2 * m_bottom + p * m_inside + m_doors;
	printf("масса шкафа равна = %lf", M);
	system("pause");
}