/*输入一个正整数，判别它是否能被3整除。若输入的不是正整数，则提示出错信息，并请用户重新输入；否则，若能被3整除，输出YES；若不能被3整除，输出NO。

输入格式:
若干行，每行一个整数。测试用例保证所有整数可以用int存储，且只有最后一个整数为正整数。

输出格式:
若干行，每行与输入的整数相对应，若输入的不是正整数，则输出error input! ，否则，若能被3整除，输出该整数加逗号，加YES；若不能被3整除，输出该整数加逗号，加NO。具体格式见样例。*/
#include <stdio.h>

int main() {
    int num;

    // 循环读取输入
    while (1) {
        // 读取输入
        while(scanf("%d", &num) != 1){
        continue;
    }
        
        // 检查是否为正整数
        if (num <= 0) {
            printf("error input!\n");
            continue;
        }

        // 判断是否能被3整除
        if (num % 3 == 0) {
            printf("%d,YES\n", num);
        } else {
            printf("%d,NO\n", num);
        }

        // 如果输入的是正整数，退出循环
        break;
    }
    return 0;
}