#include <stdio.h>

long long factorial_factors(int n) {
    long long sum = 1;
    for (int i = 2; i <= n; i++) {
        sum *= i;
    }
    return sum;
}
int main(){
    int n = 0;
    scanf("%d", &n);
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += factorial_factors(i);
    }
    printf("%lld", sum);
    return 0;
}