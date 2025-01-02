/*给定一行字符，分别统计出其中英文字母、空格、数字和其他字符的个数。

输入格式:
只有一行，为一个字符序列，字符序列长度小于100，以回车键结束。

输出格式:
只有一行，为4个用空格分隔的整数，依次代表输入字符序列中英文字符，空格，数字以及其他字符的数量。*/
#include <stdio.h>
#include <ctype.h> // 包含字符处理函数

int main() {
    char input[101]; // 假设字符序列长度小于100，加一个额外位置给字符串结束符'\0'
    int letters = 0, spaces = 0, digits = 0, others = 0;

    // 读取一行字符
    fgets(input, 101, stdin);

    // 遍历字符序列并统计
    for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
        if (isalpha(input[i])) { // 如果是英文字母
            letters++;
        } else if (isspace(input[i])) { // 如果是空格
            spaces++;
        } else if (isdigit(input[i])) { // 如果是数字
            digits++;
        } else { // 其他字符
            others++;
        }
    }

    // 输出结果
    printf("%d %d %d %d\n", letters, spaces, digits, others);

    return 0;
}