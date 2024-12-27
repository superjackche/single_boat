#include <stdio.h>
#include <string.h>

int main () {
    int ch_num[26] = {0};
    //读取&计数
    for (int i = 0; i < 4; i++) {
        char temp[101] = {0};
        fgets(temp, 100, stdin);
        int len = strlen(temp);
        for (int j = 0; j < len; j++) {
            if (temp[j] != ' ') {
                ch_num[temp[j] - 'A']++;
            }
        }
    }

    //制表
    //检索出max;
    int max = 0;
    for (int i = 0; i < 26; i++) {
        if (ch_num[i] > max) {
            max = ch_num[i];
        }
    }
    //得到max，直接开始打印，从最大列开始
    for (int i = max; i > 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (ch_num[j] >= i) printf("* ");
            else printf("  ");
        }
        printf("\n");
    }
    printf("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
}