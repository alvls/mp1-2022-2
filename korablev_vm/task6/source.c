#include "BaseFunc.h"
#include "MathFunc.h"
int Start = 0;
void main()
{
	setlocale(LC_ALL, "Rus");
	system("title ������ �������� �������");
	int mode=-1,funct; //��������� ����� � �������
	double x, ethalon; //��������� ����� � ������
	char* func[] = { "\t\t�������� �������� �������","> sin(x)","> cos(x)","> exp(x)","> arctg(x)", "> sinh(x)", "> cosh(x)", "> sec(x)", "> csc(x)" };
	char* menu[] = { "\t\t�������� ����� ���������, � ������� ������ ��������","> ����������� ������ ������� � �������� �����","> �������� �����������" };
	char* ex_prog[] = { "\t\t�������� ���������� ���","> ������� �������� ��� ������ �����","> ����� �� ���������" };
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
			printf("�������� �����, ��� ������� ������ ��������� �������� ������� (�� -1 �� 1): ");
			scanf_s("%lf", &x);
		} while (x > 1 || x < -1);
	}
	else
	{
		printf("�������� �����, ��� ������� ������ ��������� �������� ������� (� ��������): ");
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