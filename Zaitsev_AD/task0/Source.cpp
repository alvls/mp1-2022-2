#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
	setlocale(LC_CTYPE, "rus");
	float x1, x2, y1, y2, r1, r2;
	float diff, amount, length; 
	// distance - ����� ��������, length - ����������� ���������� ����� �������� �����������
	printf("������� ����� ������ ���������� � ������ ������ ���������� (x1 y1 r1): ");
	scanf_s("%f %f %f", &x1, &y1, &r1);

	printf("\n������� ����� ������ ���������� � ������ ������ ���������� (x2 y2 r2): ");
	scanf_s("%f %f %f", &x2, &y2, &r2);


	diff = fabs(r1-r2);
	amount = r1 + r2;
	length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	printf("\n>>>   ");

	if (x1 == x2 && y1 == y2 && r1 == r2) {
		printf("���������� ���������");
	}
	else if (amount == length) {
		printf("���������� �������� ������� �������");
	}
	else if (diff == length) {
		printf("���������� �������� ���������� �������");
	}
	else if (length > amount) {
		printf("���������� �� ����� ����� �����");
	}
	else if (length == 0 || length < diff) {
		printf("���� ���������� ����� ������ ������");
	}
	else if (diff < length < amount) {
		printf("���������� ������������ � ���� ������");
	}
	else if (length = 0 || length < diff) {
		printf("���� ���������� ��������� ������ ������");
	}

	printf("\n\n");
	system("pause");

	return 1;
}