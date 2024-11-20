#include <stdio.h>//通义灵码生成
#include <string.h>
#include <math.h>

// 定义一个函数来将十进制小数转换为二进制字符串
char* decimalFractionToBinary(double fraction, int precision) {
    char *binaryStr = (char*)malloc(precision + 2); // +2 是为了 "."
    strcpy(binaryStr, "0.");
    
    double temp = fraction;
    int bits = 0;
    
    while (temp != 0 && bits < precision) {
        temp *= 2;
        if (temp >= 1.0) {
            binaryStr[bits + 1] = '1';
            temp -= 1.0;
        } else {
            binaryStr[bits + 1] = '0';
        }
        bits++;
    }
    
    binaryStr[bits + 1] = '\0'; // 确保字符串正确终止
    
    return binaryStr;
}

int main() {
    double decimalFraction = 0.2; // 示例输入
    int precision = 10; // 设置精度
    
    char *binaryRepresentation = decimalFractionToBinary(decimalFraction, precision);
    
    printf("十进制小数 %.1f 的二进制表示为: %s\n", decimalFraction, binaryRepresentation);
    
    free(binaryRepresentation); // 释放内存
    
    return 0;
}