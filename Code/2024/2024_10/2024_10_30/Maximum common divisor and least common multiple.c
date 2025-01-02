#include <stdio.h>

// 计算两个数的最小值
int Min(int m, int n) {
    return m > n ? n : m;
}

// 使用欧几里得算法计算最大公约数
int Maximun_common_divisor(int m, int n) {
    while (n != 0) {
        int temp = n;
        n = m % n;
        m = temp;
    }
    return m;
}

int main() {
    int m, n, gcd, lcm;
    scanf("%d%d", &m, &n);

    // 计算最大公约数
    gcd = Maximun_common_divisor(m, n);

    // 计算最小公倍数，避免整数溢出
    lcm = (m / gcd) * n;

    // 输出结果
    printf("%d %d\n", gcd, lcm);

    return 0;
}