#include <stdio.h>
#include <math.h>

// 定义一个非常小的数，用于浮点数比较
#define EPSILON 1e-9

int is_integer(double num) {
    double int_part;
    double frac_part = modf(num, &int_part);
    if (fabs(frac_part) < EPSILON)
        return 1;
    else
        return 0;
}

long long change(double r) {
    long long count = 0;
    while (!is_integer(r)) {
        double ceil_r = ceil(r);
        r *= ceil_r;
        count++;
        if (count > 10000000)
            return 0;
    }
    return count;
}

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long k;
        scanf("%lld", &k);
        if (k == 0) {
            printf("NO!\n");
            continue;
        }
        // 检查 k 的奇偶性
        if (k % 2 == 1) {
            printf("1\n");
            continue;
        }

        double r = k + 0.5;
        long long result = change(r);
        if (result == 0)
            printf("NO!\n");
        else
            printf("%lld\n", result);
    }
    return 0;
}