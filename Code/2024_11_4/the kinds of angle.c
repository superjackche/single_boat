#include <stdio.h>
int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    if (a + b > c && a + c > b && b + c > a) {
        //存储三边长平方，简化运算，避免超时
        int a2 = a * a;
        int b2 = b * b;
        int c2 = c * c;

        if (a2 + b2 == c2 || a2 + c2 == b2 || b2 + c2 == a2) {
            printf("Right triangle\n");
        } else if (a2 + b2 > c2 && a2 + c2 > b2 && b2 + c2 > a2) {
            printf("Acute triangle\n");
        } else {
            printf("Obtuse triangle\n");
        }
        if (a == b || a == c || b == c) {
            printf("Isosceles triangle\n");
        }
        if (a == b && b == c) {
            printf("Equilateral triangle\n");
        }
    } else {
        printf("Not triangle\n");
    }
    return 0;
}