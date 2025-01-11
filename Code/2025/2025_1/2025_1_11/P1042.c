#include <stdio.h>
int main (){
    char raw[65000] = {0};  //存放输入
    int w = 0, l = 0;   //win, lose
    char temp = '0';    //暂存每个字符
    int last;
    for (int i = 0; temp != 'E'; i++) {
        temp = getchar();
        if (temp >= 'A' && temp <= 'Z') {
            if (temp == 'W') {
                raw[i] = 1;     //1表示win
            } else if (temp == 'L') {
                raw[i] = 2;     //2表示lose
            }
            last = i;
        } else i--;
    }
    //判断输赢
    //11分制
    for (int i = 0; i < last+2; i++) {
        if (raw[i] == 1) {
            w++;
        } else if (raw[i] == 2) {
            l++;
        } else if (raw[i] == 0) {
            printf("%d:%d\n", w, l);    //记录结束，输出当前分数
            break;
        }
        if (w >= 11 && w - l >= 2) {
            printf("%d:%d\n", w, l);
            w = 0, l = 0;   //输出后记得初始化w和l
        } else if (l >= 11 && l - w >= 2) {
            printf("%d:%d\n", w, l);
            w = 0, l = 0;   //输出后记得初始化w和l
        }
    }
    w = 0, l = 0;   //初始化
    printf("\n");   //mention!!!有空行
    //21分制
    for (int i = 0; i < last+2; i++) {
        if (raw[i] == 1) {
            w++;
        } else if (raw[i] == 2) {
            l++;
        } else if (raw[i] == 0) {
            printf("%d:%d\n", w, l);    //记录结束，输出当前分数
            break;
        }
        if (w >= 21 && w - l >= 2) {
            printf("%d:%d\n", w, l);
            w = 0, l = 0;   //输出后记得初始化w和l
        } else if (l >= 21 && l - w >= 2) {
            printf("%d:%d\n", w, l);
            w = 0, l = 0;   //输出后记得初始化w和l
        }
    }

    return 0;
}