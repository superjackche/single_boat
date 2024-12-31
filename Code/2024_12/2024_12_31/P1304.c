#include <stdio.h>

int prime[10001] = {2, 3};

void find_prime(int *s, int n) {
    int num = 2;
    for (int i = 4; i < n; i++) {
        int sign = 0;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                sign = 1;
                break;
            }
        }
        if (sign == 0) prime[num++] = i;
    }
}

void print_sum(int i, int n) {
    for (int j = 0; j <= n; j++) {
        for (int k = j; k <= n - j; k++) {
            if (i == prime[j] + prime[k]) {
                printf("%d=%d+%d\n", i, prime[j], prime[k]);
                return;
            }
        }
    }
}

int main () {
    int n;
    scanf("%d", &n);

    find_prime(prime, n);

    for (int i = 4; i <= n; i += 2) {
        print_sum(i, n);
    }

    return 0;
}