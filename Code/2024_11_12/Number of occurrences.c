#include <stdio.h>

int main(){
    long long n, x;
    long long num = 0;
    
    scanf("%lld %lld", &n, &x);

    for (int i = 1; i <= n; i++) {
        int a = i;
        while (a != 0) {
            int b = a % 10;
            a /= 10;
            if (b == x) num++;
        }
    }    

    printf("%lld", num);
    return 0;
}