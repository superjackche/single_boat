#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

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

// 生成长度为 n 的回文数
long long generate_palindrome(int n, int* digits) {
    long long palindrome = 0;
    int half_length = (n + 1) / 2;
    for (int i = 0; i < half_length; i++) {
        palindrome = palindrome * 10 + digits[i];
    }
    for (int i = (n % 2 == 0) ? half_length - 1 : half_length - 2; i >= 0; i--) {
        palindrome = palindrome * 10 + digits[i];
    }
    return palindrome;
}

// 生成范围 [a, b] 内的所有回文数
void generate_palindromes_in_range(long long a, long long b, long long* palindromes, int* count) {
    *count = 0;
    for (int length = 1; length <= 9; length++) {
        int half_length = (length + 1) / 2;
        int start = (length == 1) ? 1 : pow(10, half_length - 1);
        int end = pow(10, half_length);
        for (int num = start; num < end; num++) {
            int digits[half_length];
            long long temp = num;
            int i = 0;
            while (temp > 0) {
                digits[i++] = temp % 10;
                temp /= 10;
            }
            long long palindrome = generate_palindrome(length, digits);
            if (palindrome >= a && palindrome <= b) {
                palindromes[*count] = palindrome;
                (*count)++;
            }
        }
    }
}

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);

    const int max_palindromes = 1000000; // 假设最多生成 1000000 个回文数
    long long palindromes[max_palindromes];
    int count = 0;

    generate_palindromes_in_range(a, b, palindromes, &count);

    for (int i = 0; i < count; i++) {
        if (is_prime(palindromes[i])) {
            printf("%lld\n", palindromes[i]);
        }
    }

    return 0;
}