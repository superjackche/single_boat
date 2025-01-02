#include <stdio.h>
int main() {
    int n = 0;
    int ch[1024] = {0};
    int num = 1;
    int max = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ch[i]);
    }
    for (int i = 0; i < n; i++) {
        if (ch[i] + 1 == ch[i + 1]) {
            num++;
        } else {
            if (num > max) max = num;
            num = 1;
        }
    }
    printf("%d", max);
}