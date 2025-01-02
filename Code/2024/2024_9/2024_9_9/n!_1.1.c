#include <stdio.h>

int main()
{
    int n;
    long long m = 0, k = 1; // 使用 long long 类型以避免溢出
    int i = 0; // 初始化 i

    // 提示用户输入 n 的值，并读取输入
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    // 计算阶乘累加和
    for (i = 1; i <= n; i++) {
        k *= i;
        m += k;
    }

    // 输出结果
    printf("%lld\n", m); // 使用 %lld 作为 long long 的格式化输出

    return 0;
}