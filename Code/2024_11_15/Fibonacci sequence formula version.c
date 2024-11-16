#include <stdio.h>
#include <math.h>

int main() {
    long long a0 = 0;
    double a5 = 0;
    int n = 0;
    a5 = sqrt(5);
    scanf("%d", &n);
    double a1 = pow((1+a5)/2.0, n);
    double a2 = pow((1-a5)/2.0, n);
    a0 = (a1-a2)/a5;
    printf("%.2lld", a0);
    return 0;
}