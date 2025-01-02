#include <stdio.h>

int is_true_prime(int n);

int is_prime(int n);

int num_swap(int n);

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    for (int i = a; i <= b; i++) {
        if (is_true_prime(i) > 0) printf("%d\n", i);
    }
    return 0;
}

int is_true_prime(int n) {
    if (is_prime(n) > 0) {
        if (is_prime(num_swap(n)) > 0) {
            return 1;
        } else return -1;
    } else return -1;
}

int is_prime(int n) {
    for (int i = 2; i*i < n; i++) {
        if (n % i == 0) return -1;
    }
    return 1;
}

int num_swap(int n) {
    if (n > 9) {
        int temp = 0;
        temp = n % 10 * 10 + n / 10;
        return temp;
    } else return n;
}