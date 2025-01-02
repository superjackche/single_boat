#include <stdio.h>

//十进制转换为base进制的数
void transfer(long long num, int base) {  //num是十进制下的原数，base是要转换为的进制
    int p, k;
    p = 1;
    while (p <= num) {
        p *= base;  //得到大于num的最小base的次方
    }
    p /= base;  //p变为不大于num的最大base的次方
    while (p != 0) {
        k = num / p;    //其实k必小于base
        if (k < 10) {
            printf("%d", k);
        } else {
            printf("%c", k - 10 + 'A'); //用于大于十进制的进制数的表示
        }
        num %= p;   //得到剩下的部分
        p /= base;  //减少到目前base次方的更小次方
    }
}

int main(){
    long long num;
    int base;
    printf("please enter the num and base.\n");
    scanf("%d %d", &num, &base);
    transfer(num, base);
    return 0;
}