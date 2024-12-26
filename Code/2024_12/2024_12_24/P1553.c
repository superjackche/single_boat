#include <stdio.h>
#include <string.h>

// 函数声明
void type1(char *s, int len);      // 处理纯数字字符串
void type1_5(char *s, int len);    // 处理小数部分
void type2(char *s, int len);      // 处理包含小数点的字符串
void type3(char *s, int len);      // 处理包含斜杠的字符串
void type4(char *s, int len);      // 处理包含百分号的字符串

int main () {
    char s[40] = {'\0'};
    scanf("%s", s);
    int len = strlen(s);
    if (len == 1) {     // 特判单独一个0的情况
        printf("%s", s);
        return 0;
    }
    // 判断类型
    for (int i = 0; i < len; i++) {
        if (s[i] == '.') {
            type2(s, len);
            return 0;
        } else if (s[i] == '/') {
            type3(s, len);
            return 0;
        } else if (s[i] == '%') {
            type4(s, len);
            return 0;
        }
    }
    type1(s, len); // 处理纯数字
    return 0;
}

// 处理纯数字字符串，去除前导0并反转
void type1(char *s, int len) {
    // 反转字符串
    for (int i = 0; i < len/2; i++) {
        char temp = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = temp;
    }
    // 去除前导0
    int i = 0;
    while (i < len && s[i] == '0') {
        i++;
    }
    if (i == len) { // 全为0
        printf("0");
        return;
    }
    for (; i < len; i++) {
        printf("%c", s[i]);
    }
}

// 处理小数部分，反转，去除尾随0，至少保留一个0
void type1_5(char *s, int len) {
    // 反转字符串
    for (int i = 0; i < len/2; i++) {
        char temp = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = temp;
    }
    // 去除尾随0
    int new_len = len;
    while (new_len > 0 && s[new_len-1] == '0') {
        new_len--;
    }
    if (new_len == 0) { // 全为0
        printf("0");
        return;
    }
    for (int i = 0; i < new_len; i++) {
        printf("%c", s[i]);
    }
}

// 处理包含小数点的字符串
void type2(char *s, int len) {
    char integer[1024] = {0};
    char decimal[1024] = {0};
    int sign = 0;
    int len0 = 0;

    for (int i = 0, j = 0; i < len; i++) {
        if (s[i] == '.') {
            sign = 1;
            continue;
        }
        if (sign == 0) {
            integer[len0++] = s[i];
        } else if (sign == 1) {
            decimal[j++] = s[i];
        }
    }
    // 处理整数部分
    type1(integer, len0);
    printf(".");
    // 处理小数部分
    type1_5(decimal, strlen(decimal));
}

// 处理包含斜杠的字符串
void type3(char *s, int len) {
    char numerator[1024] = {0};
    char denominator[1024] = {0};
    int sign = 0;
    int len0 = 0;

    for (int i = 0, j = 0; i < len; i++) {
        if (s[i] == '/') {
            sign = 1;
            continue;
        }
        if (sign == 0) {
            numerator[len0++] = s[i];
        } else if (sign == 1) {
            denominator[j++] = s[i];
        }
    }
    // 处理分子部分
    type1(numerator, len0);
    printf("/");
    // 处理分母部分
    type1(denominator, strlen(denominator));
}

// 处理包含百分号的字符串
void type4(char *s, int len) {
    char number[1024] = {0};
    int len0 = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] != '%') {
            number[len0++] = s[i];
        }
    }
    // 处理数字部分
    type1(number, len0);
    printf("%%");
}