#include "BaseFunc.h"
#include "MathFunc.h"
int Start = 0;
void main()
{
	setlocale(LC_ALL, "Rus");
	system("title Расчет значений функций");
	int mode=-1,funct; //выбранный режим и функция
	double x, ethalon; //выбранная точка и эталон
	char* func[] = { "\t\tВыберите желаемую функцию","> sin(x)","> cos(x)","> exp(x)","> arctg(x)", "> sinh(x)", "> cosh(x)", "> sec(x)", "> csc(x)" };
	char* menu[] = { "\t\tВыберите режим программы, с которым хотите работать","> Однократный расчет функции в заданной точке","> Серийный эксперимент" };
	char* ex_prog[] = { "\t\tВыберите дальнейший шаг","> Рассчет значения для другой точки","> Выйти из программы" };
	typedef void (*function) (double, double, int);
	function math_func[6] = { &GetSin, &GetCos, &GetExp, &GetArctg, &GetSh, &GetCosh};
	typedef double (*eth_function) (double);
	eth_function eth_func[6] = { &sin, &cos, &exp, &atan, &sinh, &cosh,};
	hello(Start);
	Start = 1;
	mode = menu_mode(menu, 3);
	funct = menu_mode(func, 7);
	system("cls");
	if (funct == 4 || funct == 3 )
	{
		do {
			system("cls");
			printf("Выберите точку, для которой хотите расчитать значение функции (от -1 до 1): ");
			scanf_s("%lf", &x);
		} while (x > 1 || x < -1);
	}
	else
	{
		printf("Выберите точку, для которой хотите расчитать значение функции (в градусах): ");
		scanf_s("%lf", &x);
		x = x * M_PI / 180;
	}
	ethalon = eth_func[funct - 1](x);
	switch (mode)
	{
	case 1:
		FirstMode(math_func[funct-1], x, ethalon);
		break;
	case 2:
		SecondMode(math_func[funct - 1], x, ethalon);
		break;
	}
	system("pause");
	mode = menu_mode(ex_prog, 3);
	switch (mode)
	{
	case 1:
		system("cls");
		main();
		break;
	case 2:
		exit_prog();
		break;
	}
}