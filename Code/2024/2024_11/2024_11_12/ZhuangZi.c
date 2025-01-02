#include <stdio.h>
#include <math.h>

int main() {
    double a = 0;
    int day = 1;
    scanf("%lf", &a);
    while (a != 1) {
        a = floor(a / 2.0);
        day++;
    }
    printf("%d", day);
    return 0;
}