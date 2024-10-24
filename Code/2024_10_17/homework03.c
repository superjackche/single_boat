/*给定正整数a，b，c。求不定方程 ax+by=c 关于未知数x和y的所有非负整数解组数。

注：题目来自信息学奥赛一本通

输入格式:
只有一行，为三个用空格分隔的正整数，依次代表a，b，c。每个数均不大于1000。测试用例保证合法。

输出格式:
只有一个整数，即不定方程的非负整数解组数。

输入样例:
2 3 18

输出样例:
4
*/
#include <stdio.h>
int main(){
    int a, b, c;
    int num = 0;
    scanf("%d %d %d", &a, &b, &c);
    for (int i = 0; i <= c; i++) {
        for (int j = 0; j <= c; j++) {
            if (a * i + b * j == c) {
                num++;
            }
        }
    }
    printf("%d", num);
    return 0;
}