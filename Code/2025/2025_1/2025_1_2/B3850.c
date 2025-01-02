#include <stdio.h>
#include <string.h>

int is_lucky(char *s, int len);

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char num[1024] = {'\0'};
        scanf("%s", num);
        if (is_lucky(num, strlen(num)) > 0) printf("T\n");
        else printf("F\n");
    }
}

int is_lucky(char *s, int len) {
    // 从右往左遍历（！！！）
    for (int i = len - 1; i >= 0; i--) {
        // 计算这是第几位(从右至左)
        int pos = (len - 1 - i) + 1;  // pos = 1 表示个位

        // 如果是奇数位 => 做乘7及拆分
        if (pos % 2 == 1) {
            int num = s[i] - '0';
            num *= 7;
            // 不断拆分为各位数之和, 直到 < 10
            while (num > 9) {
                int temp = 0;
                while (num > 0) {
                    temp += num % 10;
                    num /= 10;
                }
                num = temp;
            }
            // 放回字符串
            s[i] = (char)(num + '0');   // 记得char类型变换
        }
        // 如果是偶数位 => 不变
    }

    long long sum = 0;
    // 求各位和
    for (int i = 0; i < len; i++) {
        sum += s[i] - '0';
    }

    // 判断8的倍数
    if (sum % 8 == 0) {
        return 1;
    } else {
        return 0;
    }
}