#include <stdio.h>

long long factorial(int n) {
    if (n != 1) {
        return n * factorial(n-1);
    } else {
        return 1;
    }
}

int main (){
    int n = 0;
    scanf("%d", &n);
    long long ans = factorial(n);
    printf("%lld", ans);
    return 0;
}