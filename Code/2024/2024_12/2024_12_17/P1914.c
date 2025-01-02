#include <stdio.h>
#include <string.h>
int main (void) {
    char raw[52] = {0};
    char ans[52] = {0};
    int n;
    scanf("%d", &n);
    n %= 26;
    scanf("%s", raw);
    int len = strlen(raw);
    for (int i = 0; i < len; i++) {
        if (raw[i] + n > 'z') {    //首先检查是否要循环，并且不能对数组ascll码直接操作（我也不知道为啥）
            n -= 26;    //选择对n操作
        }
        ans[i] = raw[i] + n;
    }
    printf("%s", ans);
    return 0;
}