#include <stdio.h>

int prime(int n) {
    for (int i = 2; i*i < n; i++) {
        if (n % i == 0) return 0;
    }
    return n;
}

int main() {
    long n = 0;
    scanf("%ld", &n);
    for (int i = 2; i < n; i++) {
        if (prime(i) != 0) {
            if (n % i == 0) {
                printf("%d", n/i);
                return 0;
            }
        }
    }
}