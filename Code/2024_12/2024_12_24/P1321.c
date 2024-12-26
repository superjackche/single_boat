#include <stdio.h>
#include <string.h>

int main () {
    char ch[300] = {0};
    scanf("%s", ch);
    int len = strlen(ch);
    int boy_num = 0;
    int girl_num = 0;

    for (int i = 0; i < len; i++) {
        if (ch[i] == 'b') {
            boy_num++;
            if (ch[i+1] == 'o') {
                ch[i+1] = 1;
                if (ch[i+2] == 'y') {
                    ch[i+2] = 1;
                }
            }
        } else if (ch[i] == 'g') {
            girl_num++;
            if (ch[i+1] == 'i') {
                ch[i+1] = 1;
                if (ch[i+2] == 'r') {
                    ch[i+2] = 1;
                    if (ch[i+3] == 'l') {
                        ch [i+3] = 1;
                    }
                }
            }
        } else if (ch[i] == 'o') {
            boy_num++;
            ch[i] = 1;
            if (ch[i+1] == 'y') {
                ch[i+1] = 1;
            }
        } else if (ch[i] == 'y') {
            boy_num++;
            ch[i] = 1;
        } else if (ch[i] == 'i') {
            girl_num++;
            ch[i] = 1;
            if (ch[i+1] == 'r') {
                ch[i+1] = 1;
                if (ch[i+2] == 'l') {
                    ch[i+2] = 1;
                }
            }
        } else if (ch[i] == 'r') {
            girl_num++;
            ch[i] = 1;
            if (ch[i+1] == 'l') {
                ch[i+1] = 1;
            }
        } else if (ch[i] == 'l') {
            girl_num++;
            ch[i] = 1;
        }
    }

    printf("%d\n%d", boy_num, girl_num);
}