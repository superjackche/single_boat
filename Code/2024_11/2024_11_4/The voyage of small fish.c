#include <stdio.h>

int main() {
    int x = 0;
    long long n = 0, sum = 0;
    scanf("%d %lld", &x, &n);

    // 计算完整的周数和剩余的天数
    long long complete_weeks = n / 7;
    long long remaining_days = n % 7;

    // 计算完整周数的游泳距离
    sum += 250 * 5 * complete_weeks;

    // 计算剩余天数的游泳距离
    for (int i = 0; i < remaining_days; i++) {
        int current_day = (x + i - 1) % 7 + 1; // 计算当前是周几
        if (current_day <= 5) { // 工作日
            sum += 250;
        }
    }

    printf("%lld", sum);
    return 0;
}