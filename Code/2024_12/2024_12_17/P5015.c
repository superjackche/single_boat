#include <stdio.h>
#include <string.h>
int main () {
    int num = 0;
    char ch[101];
    fgets(ch, sizeof(ch), stdin);
    for (int i = 0; i < sizeof(ch) && ch[i] != '\0'; i++) {
        if (ch[i] != ' ' && ch[i] != '\n') num++;
    }
    printf("%d", num);
}