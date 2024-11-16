#include <stdio.h>
#include <ctype.h>

int main() {
    int t;
    char str[32]; // 字符串长度不超过30，加1用于存储结束符

    // 读取测试用例数量
    scanf("%d", &t);
    getchar(); // 吸收换行符

    while (t--) {
        fgets(str, sizeof(str), stdin); // 读取一行字符串
        int len = 0;
        
        while (str[len] != '\n' && str[len] != '\0') {
            len++;
        }
        str[len] = '\0'; // 去掉换行符

        // 检查字符串是否为空
        if (len == 0) {
            printf("no\n");
            continue;
        }

        // 检查前导0
        if (str[0] == '0' && len > 1) {
            printf("no\n");
            continue;
        }

        // 检查正负号
        int i = 0;
        if (str[0] == '+' || str[0] == '-') {
            i++;
            if (i >= len || str[i] == '0') {
                printf("no\n");
                continue;
            }
        }

        // 检查剩余字符
        for (; i < len; i++) {
            if (!isdigit(str[i])) {
                printf("no\n");
                break;
            }
        }

        if (i == len) {
            printf("yes\n");
        }
    }

    return 0;
}