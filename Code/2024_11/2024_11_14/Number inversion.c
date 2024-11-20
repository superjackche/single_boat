#include <stdio.h>
#include <stdlib.h> // for abs()

long long reverse_number(long long n) {
    long long reversed = 0;
    int is_negative = n < 0;
    n = abs(n); // 处理负数

    while (n > 0) {
        int digit = n % 10;
        reversed = reversed * 10 + digit;
        n /= 10;
    }

    if (is_negative) {
        reversed = -reversed;
    }

    return reversed;
}

int main() {
    long long n;
    scanf("%lld", &n);

    long long result = reverse_number(n);
    printf("%lld\n", result);

    return 0;
}