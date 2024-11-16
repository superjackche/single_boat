#include <stdio.h>
#include <math.h>

int main() {
    int num, len;
    int a = 0, b = 0;
    int a0 = a;
    scanf("%d %d", &num, &len);
    int num0 = num;
    int num1 = num;
    if (len%2 == 1) {
        for (int j = 0; j < len/2; j++) {
            for (int i = 1; i < len; i++) {
                a = num0/10;
                num0 /= 10;
            }
            for (int i = 2; i < len; i++) {
                a0 = num1/10;
                num1 /= 10;
            }
            for (int i = len; i > 0; i--) {
                b = num1/10;
                num1 /= 10;
            }
            if (a == b) {
                printf("%d %d\n", a, b);
            } else {
                printf("%d %d\nNo", a, b);
                return 0;
            }
            if (j+1 == len/2) {
                printf("%d %d\n", num1%10, num1%10);
            }
        }
    } else {
        for (int j = 0; j < len/2; j++) {
            for (int i = j; i < len; i++) {
                a = num0/10;
                num0 /= 10;
            }
            for (int i = len; i > 0; i--) {
                b = num1/10;
                num1 /= 10;
            }
            if (a == b) {
                printf("%d %d\n", a, b);
            } else {
                printf("%d %d\nNo", a, b);
                return 0;
            }
        }
    }
    printf("Yes");
}