#include <stdio.h>
int main(){
    float a, b, c, max1, max2, k;
    scanf("%f%f%f", &a, &b, &c);
    if (a >= b) {
        max1 = a;
        if (b >= c) {
            max2 = b;
        } else {
            max2 = c;
        }
    } else {
        max1 = b;
        if (a >= c) {
            max2 = a;
        } else {
            max2 = c;
        }
    }
    k = (max1 + max2)/2;
    printf("%.1f", k);
    return 0;
}