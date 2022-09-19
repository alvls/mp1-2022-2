#include <stdio.h>
#include <math.h>
#include <locale.h>

void main() {
	double x_1, y_1, x_2, y_2, radius1, radius2;
	double distanceBetweenCenters;	

	// Установка русского языка 
	setlocale(LC_ALL, "Russian");

	// Вместо функции scanf используется scanf_s по указанию компилятора Visual Studio 

	printf("Введите координаты и радиус первой точки: ");
	scanf_s("%lf%lf%lf", &x_1, &y_1, &radius1);

	printf("Введите координаты и радиус второй точки: ");
	scanf_s("%lf%lf%lf", &x_2, &y_2, &radius2);


	// Расстояние между центрами окружностей
	distanceBetweenCenters = sqrt(pow(x_1 - x_2, 2) + pow(y_1 - y_2, 2));


	// Окружности не имеют общих точек (2 различных случая)
	if (distanceBetweenCenters > (radius1 + radius2))
	{
		printf("Окружности не имеют общих точек, при этом одна из них не находится внутри другой");
	};

	if (distanceBetweenCenters < (fabs(radius1 - radius2)))
	{
		printf("Окружности не имеют общих точек, при этом одна из них находится внутри другой");
	};


	// Окружности имеют одну общую точку (2 различных случая)
	if (distanceBetweenCenters == (radius1 + radius2))
	{
		printf("Окружности имеют одну общую точку (касаются внешним образом)");
	};
	
	// Здесь делаем дополнительную проверку на то, не совпадают ли окружности
	if (distanceBetweenCenters == fabs(radius1 - radius2) && ((radius1 != radius2) || (distanceBetweenCenters != 0)))
	{
		printf("Окружности имеют одну общую точку (касаются внутренним образом)");
	};


	// Окружности имеют две общие точки (пересекаются)
	if ((fabs(radius1 - radius2) < distanceBetweenCenters) && (distanceBetweenCenters < (radius1 + radius2)))
	{
		printf("Окружности имеют две общие точки (пересекаются)");
	}


	// Окружности совпадают
	if ((distanceBetweenCenters == 0) && (radius1 == radius2))
	{
		printf("Окружности совпадают");
	}

	// Используем функцию getch, чтобы консоль закрывалась не сразу, а после нажатия какой-нибудь клавиши
	_getch();
}