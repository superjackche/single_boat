#include <stdio.h>

//ʮ����ת��Ϊbase���Ƶ���
void transfer(long long num, int base) {  //num��ʮ�����µ�ԭ����base��Ҫת��Ϊ�Ľ���
    int p, k;
    p = 1;
    while (p <= num) {
        p *= base;  //�õ�����num����Сbase�Ĵη�
    }
    p /= base;  //p��Ϊ������num�����base�Ĵη�
    while (p != 0) {
        k = num / p;    //��ʵk��С��base
        if (k < 10) {
            printf("%d", k);
        } else {
            printf("%c", k - 10 + 'A'); //���ڴ���ʮ���ƵĽ������ı�ʾ
        }
        num %= p;   //�õ�ʣ�µĲ���
        p /= base;  //���ٵ�Ŀǰbase�η��ĸ�С�η�
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