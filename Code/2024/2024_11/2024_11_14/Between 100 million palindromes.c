#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// 判断一个数是否为回文数
bool is_palindrome(long long n) {
    char str[20];
    sprintf(str, "%lld", n);
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

// 判断一个数是否为质数
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);

    for (long long i = a; i <= b; i++) {
        if (is_palindrome(i) && is_prime(i)) {
            printf("%lld\n", i);
        }
    }

    return 0;
}