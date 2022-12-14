#define _CRT_SECURE_NO_WARNINGS //подтверждаем, что готовы использовать не очень безопасную функцию scanf()
#include <locale.h> // локализация
#include < string.h >

#include <stdio.h>;  // обязательная часть каждой программы с вводом-выводом
#include <math.h>;   // математические операции

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