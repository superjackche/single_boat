#include <stdio.h>

int pow0(int base, int exponent) {
    int result = 1;
    while (exponent--) {
        result *= base;
    }
    return result;
}

int main(void) {
    int num, len;
    scanf("%d %d", &num, &len);

    int temp_num = num; // 保存原始数字

    for (int i = 1; i <= len / 2; i++) {
        int high = (num / pow0(10, len - i)) % 10;
        int low = (temp_num % pow0(10, i)) / pow0(10, i - 1);

        printf("%d %d\n", high, low);

        if (high != low) {
            printf("No\n");
            return 0;
        }
    }

    // 若长度为奇数，需要输出中间位
    if (len % 2 == 1) {
        int mid_digit = (num / pow0(10, len / 2)) % 10;
        printf("%d %d\n", mid_digit, mid_digit);
    }

    printf("Yes\n");
    return 0;
}