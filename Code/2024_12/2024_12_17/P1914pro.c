#include <stdio.h>
#include <string.h>

int main(void) {
    char raw[52] = {0};
    char ans[52] = {0};
    int n;
    scanf("%d", &n);
    n %= 26;
    scanf("%s", raw);
    int len = strlen(raw);
    for (int i = 0; i < len; i++) {
        if (raw[i] >= 'a' && raw[i] <= 'z') {
            ans[i] = 'a' + (raw[i] - 'a' + n) % 26;
        } else if (raw[i] >= 'A' && raw[i] <= 'Z') {
            ans[i] = 'A' + (raw[i] - 'A' + n) % 26;
        } else {
            ans[i] = raw[i]; // 非字母字符不处理
        }
    }
    printf("%s", ans);
    return 0;
}