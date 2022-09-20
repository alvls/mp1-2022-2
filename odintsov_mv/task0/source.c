#include <stdio.h>
#include <math.h>
int main() {
    float x1, y1, r1;
    float x2, y2, r2;
    float distance;
    printf("Enter the data (x,y,r) for the first circle \n");
    scanf_s("%f%f%f", &x1, &y1, &r1);
    printf("Enter the data (x,y,r) for the second circle \n");
    scanf_s("%f%f%f", &x2, &y2, &r2);
    distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    // окружности равны +
    if (distance==0 && r1==r2) {
        printf("Circles are equal");
    }
    // окружности касаются внешним образом +
    if (distance == r1 + r2) {
        printf("Circles touch externally");
    }
    // окружности касаются внутренним образом +
    if (distance == abs(r1 - r2)) {
        printf("Circles touch internally");
    }
    // окружности не касаются +
    if (distance > (r1 + r2)) {
        printf("Circles do not touch");
    }
    //одна окружность внутри другой +
    if (distance < abs(r1 - r2)) {
        printf("One circle inside another");
    }
    //окружности пересекаются в двух точках 
    if ((distance<(r1 + r2)) && (distance> abs(r1 - r2))) {
        printf("Circles intersect at two points");
    }
    
 
























    system("pause");
}