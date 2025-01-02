#include <stdio.h>

int is_prime(int num) {
    if (num == 1) return -1;
    if (num <= 3) return num;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return -1;
    }
    return num;
}

int main () {
    int n;
    scanf("%d", &n);
    int num[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }

    for (int i = 0; i < n; i++) {
        if (is_prime(num[i]) != -1) {
            printf("%d ", num[i]);
        }
    }
}