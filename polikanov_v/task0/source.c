#define _CRT_SECURE_NO_WARNINGS //������������, ��� ������ ������������ �� ����� ���������� ������� scanf()
#include <locale.h> // �����������
#include < string.h >

#include <stdio.h>;  // ������������ ����� ������ ��������� � ������-�������
#include <math.h>;   // �������������� ��������

char* no_space(char* mass) {
    char copy[80];
    int k = 0;
    int i = 0;
    char c;
    int len = strlen(mass);
    while (k < len) {
        if (mass[i] != ' ') {
            copy[k] = mass[i];
            k++;
            i++;
        
        }
        else if (mass[i] == ' ' && i % 2 != 0){
            copy[k] = mass[i];
            k++;
            i++;
        }
        else {
            i++;
        }
    }
    copy[k] = '\0';
    return copy;
}
void main() {

}