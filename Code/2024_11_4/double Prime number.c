#include <stdio.h>
#include <math.h>

int is_prime_num(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int double_prime(int m, int n) {
    for (int i = m; i <= n - 2; i++) {
        if (is_prime_num(i) == 1 && is_prime_num(i + 2) == 1) {
            printf("%d,%d\n", i, i + 2);
        }
    }
}

int main() {
    int m = 0, n = 0;
    scanf("%d,%d", &m, &n);
    double_prime(m, n);
    return 0;
}