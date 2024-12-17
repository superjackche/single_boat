#include <stdio.h>
#include <string.h>
int main () {
    int num = 0;
    char ch[101] = {0};
    fgets(ch, sizeof(ch), stdin);
    for (int i = 0; i < sizeof(ch); i++) {
        if (ch[i] != ' ' && ch[i] != '\n') num++;
    }
    printf("%d", num);
}