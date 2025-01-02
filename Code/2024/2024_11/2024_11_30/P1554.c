#include <stdio.h>
#include <string.h>

int main() {
    long long m, n;
    scanf("%lld %lld", &m, &n);  // 修正格式化字符串

    int ans[10] = {0};  // 数组大小为10，表示数字0-9

    for (long long i = m; i <= n; i++) {
        char ch[21];
        sprintf(ch, "%lld", i);  // 将整数转换为字符串
        for (int j = 0; j < strlen(ch); j++) {
            ans[ch[j] - '0']++;  // 将字符数字转换为整数索引
        }
    }

    for (int k = 0; k < 10; k++) {
        printf("%d ", ans[k]);  // 输出每个数字出现的次数
    }
    return 0;
}