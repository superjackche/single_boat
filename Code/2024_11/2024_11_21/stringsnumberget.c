#include <stdio.h>
#include <ctype.h>

int main(void) {
    double sum = 0.0;          // 用于存储所有金额的总和
    double num = 0.0;          // 当前正在解析的数字
    int in_num = 0;            // 标志是否在解析数字（0表示否，1表示是）
    int has_dot = 0;           // 标志当前数字是否已经遇到小数点
    double frac_multiplier = 0.1; // 小数部分的乘数

    int ch; // 使用int以正确处理EOF

    // 逐字符读取输入
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (isdigit(ch)) { // 如果是数字字符
            if (!in_num) { // 开始解析一个新的数字
                in_num = 1;
                num = 0.0;
                has_dot = 0;
                frac_multiplier = 0.1;
            }
            if (!has_dot) {
                num = num * 10 + (ch - '0'); // 累加整数部分
            } else {
                num += (ch - '0') * frac_multiplier; // 累加小数部分
                frac_multiplier *= 0.1; // 更新小数部分的乘数
            }
        }
        else if (ch == '.') { // 如果是小数点
            if (in_num && !has_dot) { // 只在当前在解析数字且未遇到小数点时处理
                has_dot = 1;
            }
            // 如果已经遇到小数点或未在解析数字，则忽略
        }
        else { // 其他字符（小写字母）
            if (in_num) { // 如果之前在解析一个数字，结束当前数字的解析
                sum += num;
                in_num = 0;
                num = 0.0;
            }
            // 其他字符无需处理
        }
    }

    // 如果最后一个字符仍在解析数字，加入总和
    if (in_num) {
        sum += num;
    }

    // 输出总和，保留三位小数
    printf("%.3lf\n", sum);

    return 0;
}