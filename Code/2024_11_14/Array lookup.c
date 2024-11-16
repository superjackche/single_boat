#include <stdio.h>
int main() {
    int ch[1024] = {0}, num[1024] = {0};
    int n, m;
    scanf("%d", &n);
    //对于n = 1时，输出应为NULL，然而右侧仍有无关数据（0），故要另行讨论
    if (n == 1) {
        printf("NULL\n");
        return 0;
    } else {
        for (int i = 0; i < n; i++) {
        scanf("%d", &ch[i]);
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &num[i]);
        }
        for (int i = 0; i < m; i++) {
            int sign = 1;
            for (int j = 0; j < n; j++) {
                if (num[i] == ch[j]) {
                    if (j == 0) {
                        printf("%d\n", ch[1]);
                        sign = 0;
                    } else if (j == n-1) {
                        printf("%d\n", ch[n-2]);
                        sign = 0;
                    } else {
                        printf("%d %d\n", ch[j-1], ch[j+1]);
                        sign = 0;
                    }
                }
            }
            if (sign) printf("NULL\n");
        }
    }
    return 0;
}    