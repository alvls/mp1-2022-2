#include <stdio.h>
#include <math.h>
#include <locale.h>
void main()
{
	setlocale(LC_ALL, "Rus");
	float h, d, w;
	float m;
	float Pdsp, Pdvp, Ptree;
	int count;
	printf("Ведите последовательно: высоту, ширину и глубину шкафа(в сантиметрах) ");
	scanf_s("%f %f %f", &h, &w, &d);
	if ((h < 180) || (h > 220)) printf("Некорректно введена высота шкафа ");
	else if ((w < 80) || (w > 120)) printf("Некорректно введена ширина шкафа ");
	else if ((d < 50) || (d > 90)) printf("Некорректно введена глубина шкафа ");
	else
	{
		count = 0;
		while (h > 40)
		{
			h = h - 40;
			count++;
		}
		h = h + count * 40;
		printf("Ведите последовательно плотности ДСП, ДВП и дерева(в м^3/кг) ");
		scanf_s("%f %f %f", &Pdsp, &Pdvp, &Ptree);
		if (Pdsp <= 0) printf("Некорректно введена плотность ДСП ");
		else if (Pdvp <= 0) printf("Некорректно введена плотность ДВП ");
		else if (Ptree <= 0) printf("Некорректно введена плотность дерева ");
		else
		{
			m = (Pdvp * h * w * 0.5 + Pdsp * 2 * d * 1.5 * (w + h) + Ptree * h * w + Pdsp * 1.5 * (w - 3) * d * count) / 1000000;
			printf("Масса шкафа = %f ", m);
		}
	}
	system("pause");
}