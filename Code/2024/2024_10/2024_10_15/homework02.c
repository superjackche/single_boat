/*请你写一段程序，统计各类数字的占比。

提示：输出%时需要用%%才能输出。

输入格式:
只有一行，为用空格分隔的若干整数，最后一个整数为0。测试用例保证输入中只包含这一个0。

输出格式:
共三行，依次分别输出3、5、7的倍数的占比（如果某个数同时为多个数的倍数，如15，70等，则不参与统计，但要计到总数中）。占比采用百分数形式，且保留2位小数。这里的占比指的是这类数字的数量跟所有数字的总数（不包括最后的0）比。测试用例保证所有整数可以用int存储。*/
#include <stdio.h>
int main(){
    int num, sum = 0;
    int num3 = 0, num5 = 0, num7 = 0;

    while (scanf("%d", &num) == 1){
        if (num == 0) break;

        sum++;
        if (num % 3 == 0 && num % 5 != 0 && num % 7 != 0) {
            num3++;
        } else if (num % 5 == 0 && num % 3 != 0 && num % 7 != 0) {
            num5++;
        } else if (num % 7 == 0 && num % 5 != 0 && num % 3 != 0) {
            num7++;
        }
    }
 
    double p3 = (double)num3 / sum * 100;
    printf("%.2f%%\n", p3);
    double p5 = (double)num5 / sum * 100;
    printf("%.2f%%\n", p5);
    double p7 = (double)num7 / sum * 100;
    printf("%.2f%%\n", p7);
    return 0;
}