#include <stdio.h>
#include <locale.h>
#include <math.h>//инклюды 
int shelves_count(float h)//функция подсчета количества полок
{
	float sh_count = 0, ThicknessUsed = 40;
	while ((ThicknessUsed+1.5)<=h)
	{
		sh_count = sh_count + 1; 
		ThicknessUsed = ThicknessUsed + 41.5; 
	}
	return (int)sh_count;
}
void main()
{
	setlocale(LC_ALL, "Rus");//локализация
	//задание переменных и констант 
	float h = 0, w = 0, d = 0,m; //задаваемые размеры шкафа
	float dsp, dvp, wood;//плотности материалов
	float t_dsp = 1.5, t_dvp = 0.5, t_door = 1; //толщины материалов
	int sh;//количество полок
	//
	//получение переменных + проверка данных 
	while ((h < 180) || (h > 220))
	{
		printf("Введите высоту (от 180 до 220 см) задней стенки ");
		scanf("%f", &h);
	}
	while ((w < 80) || (w > 120))
	{
		printf("Введите ширину (от 80 до 120 см) задней стенки ");
		scanf("%f", &w);
	}
	while ((d < 50) || (d > 90))
	{
		printf("Введите глубину (от 50 до 90 см) шкафа ");
		scanf("%f", &d);
	}
	printf("Подсказка! Принятые плотности материалов: ДВП = 400 кг/м ДСП = 750 кг/м Дерево = 650 кг/м \n");
	printf("Введите плотность ДВП, ДСП и дерева в кг/кубометр ");
	scanf("%f %f %f", &dvp, &dsp, &wood);
	sh = shelves_count(h);
	//
	//математические рассчеты
	dvp = dvp / 1000000; //приведение плотностей к кг/кубический сантиметр
	dsp = dsp / 1000000;
	wood = wood / 1000000;
	m = (h * w * t_dvp * dvp) + (2 * h * d * t_dsp * dsp) + (2 * w * d * t_dsp * dsp) + (h * w * t_door * wood) + (sh * w * d * t_dsp * dsp);
	printf("Масса шкафа равна %f кг \n", m);
	system("pause");
	//
}