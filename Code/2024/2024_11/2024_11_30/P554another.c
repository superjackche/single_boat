#include <stdio.h>

int main() {
    long long m, n;
    scanf("%lld %lld", &m, &n);  // 读取范围 m 到 n

    int ans[10] = {0};  // 统计0-9各个数字出现的次数，初始化为0

    for (long long i = m; i <= n; i++) {
        if (i == 0) {
            ans[0]++;  // 特殊情况：数字为0，统计0出现一次
            continue;
        }

        long long temp = i;  // 临时变量用于提取数字

        while (temp > 0) {
            int digit = temp % 10;  // 提取最低位数字
            ans[digit]++;           // 统计该数字出现的次数
            temp /= 10;             // 去掉最低位数字
        }
    }

    for (int k = 0; k < 10; k++) {
        printf("%d ", ans[k]);  // 输出0-9各个数字的出现次数
    }
    printf("\n");  // 输出换行符

    return 0;
}