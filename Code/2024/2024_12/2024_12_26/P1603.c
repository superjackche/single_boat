#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定义英文数字字符串数组，使用双引号初始化
char eng_num[27][20] = {"zero", "one", "two", "three", "four", "five",
                        "six", "seven", "eight", "nine", "ten",
                        "eleven", "twelve", "thirteen", "fourteen", "fifteen",
                        "sixteen", "seventeen", "eighteen", "nineteen", "twenty",
                        "a", "both", "another", "first", "second", "third"};

// 冒泡排序函数，用于对整数数组进行排序
void sort(int *s, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j] > s[j+1]) {
                int temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
}

int main () {
    int num[6] = {0}; // 存储转换后的数值，最大输入6个单词
    int m = 0;        // 计数器
    
    for (int i = 0; i < 6; i++) { // 假设有6个输入
        char temp[20] = {0};
        scanf("%s", temp); // 读取输入字符串
        
        // 查找输入字符串在 eng_num 数组中的位置
        int found = 0; // 标志位，表示是否找到匹配
        for (int k = 0; k < 27; k++) {
            if (strcmp(eng_num[k], temp) == 0) {
                int x;
                if (k <= 20) {
                    x = k;
                }
                else {
                    // 根据非正规词汇单独指定映射值
                    if (k == 21) { // "a"
                        x = 1;
                    }
                    else if (k == 22) { // "both"
                        x = 2;
                    }
                    else if (k == 23) { // "another"
                        x = 1;
                    }
                    else if (k == 24) { // "first"
                        x = 1;
                    }
                    else if (k == 25) { // "second"
                        x = 2;
                    }
                    else if (k == 26) { // "third"
                        x = 3;
                    }
                }
                // 计算 y = (x * x) % 100
                int y = (x * x) % 100;
                num[m++] = y;
                found = 1;
                break;
            }
        }
        if (!found) {
            continue;
        }
    }

    // 对转换后的数值数组进行排序
    sort(num, m);
    
    // 处理前导0，统一更换成-1便于处理
    int j = 0;

    while (num[j] == 0) {
        num[j++] = -1;
    }

    int is_print = 0;
    int sign = 0;
    for (int i = 0; i < m; i++) {
        if (num[i] != -1) {
            if (sign == 0) {
                printf("%d", num[i]);
                sign = 1;
                is_print = 1;
            } else {
                printf("%.2d", num[i]);
                is_print = 1;
            }
        }
    }

    if (is_print == 0) printf("0");

    return 0;
}