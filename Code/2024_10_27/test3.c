#include <stdio.h>
/*
int main(){
    char ch;
    int sum = 0;
    while ((ch = getchar()) != '\n') {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            putchar(ch);
        } else {
            sum++;
        }
    }
    printf("\n");
    printf("%d", sum);
    return 0;
}
*/
int main() {
    int ignoredCount = 0;
    char ch;

    // 读取输入字符
    /*
    while (scanf("%c", &ch) = EOF && ch != '\n')为什么程序无法运行
    首先，考试中=和==有区别，应为==
    其次，原始代码中的条件 scanf("%c", &ch) == EOF && ch != '\n' 存在逻辑问题。
    scanf("%c", &ch) 返回值为读取到的字符数，当读取到文件结束符（EOF）时返回 EOF，否则返回 1。
    因此，scanf("%c", &ch) == EOF 和 ch != '\n' 这两个条件不可能同时为真，因为当 scanf 返回 EOF 时，ch 的值是未定义的。
    */
    //while (scanf("%c", &ch) == 1 && ch != '\n') {
    while (ch != 'n') {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            printf("%c", ch);
        } else {
            ignoredCount++;
        }
    }
    /*while (scanf("%c", &ch) == 1) {
        if (ch == '\n') {
            break; // 遇到换行符，结束循环
        }
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            printf("%c", ch);
        } else {
            ignoredCount++;
        }
    }while (scanf("%c", &ch) == 1) {
        if (ch == '\n') {
            break; // 遇到换行符，结束循环
        }
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            printf("%c", ch);
        } else {
            ignoredCount++;
        }
    }*/

    // 输出换行符
    printf("\n");

    // 输出被忽略的字符数量
    printf("%d\n", ignoredCount);

    return 0;
}