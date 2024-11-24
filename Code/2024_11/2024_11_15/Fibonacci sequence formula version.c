#include <stdio.h>
#include <math.h>

int main() {
    long long n;
    scanf("%lld", &n);
    printf("%.2lf", pow(((1+sqrt(5))/2),n)-pow(((1-sqrt(5))/2),n)/sqrt(5));
    return 0;
}