#include <stdio.h>
#include <string.h>
int main () {
    int n;
    char ch[102] = {0};
    int ans = 0;

    scanf("%d", &n);
    scanf("%s", ch);

    int len = strlen(ch);
    for (int i = 0; i < len; i++) {
        if (ch[i] == 'V' && ch[i+1] == 'K') {
            ch[i] = 'A';
            ch[i+1] = 'A';
            ans++;
        }
    }

    for (int i = 0; i < len; i++) {
        if (ch[i] != 'A' && ch[i] == ch[i+1]) {
            ans++;
            break;
        }
    }

    printf("%d", ans);
}