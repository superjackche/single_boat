/*已知一个整数n，你要根据n打印出n阶的实心菱形。

输入格式:
只有一个整数n(0<n<40，代表要打印的菱形阶数)。测试用例保证合法。

输出格式:
n阶实心菱形(占2乘n-1行)。*/
#include <stdio.h>

void printSpaces(int count) {
    for (int j = 1; j <= count; j++) {
        printf(" ");
    }
}

void printStars(int count) {
    for (int k = 1; k <= count; k++) {
        printf("*");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    // 验证输入
    if (n < 1 || n > 39) {
        printf("Error: Invalid input (0 < n < 40)\n");
        return 1;
    }

    // 打印上半部分
    for (int i = 1; i <= n; i++) {
        printSpaces(n - i);
        printStars(2 * i - 1);
        printf("\n");
    }

    // 打印下半部分
    for (int i = n - 1; i >= 1; i--) {
        printSpaces(n - i);
        printStars(2 * i - 1);
        printf("\n");
    }

    return 0;
}