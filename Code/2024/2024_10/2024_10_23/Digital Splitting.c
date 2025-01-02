#include <stdio.h>

// 递归函数，用于打印数字的每一位
void print_digits_recursively(int n) {
    if (n < 10) {
        // 如果 n 是一位数，直接输出
        printf("%d", n);
    } else {
        // 先递归处理高位数字
        print_digits_recursively(n / 10);
        // 再输出当前位数字
        printf(" %d", n % 10);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // 调用递归函数处理并输出结果
    print_digits_recursively(n);
    printf("\n");

    return 0;
}