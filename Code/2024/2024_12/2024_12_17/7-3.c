#include <stdio.h>
int main (void) {
    int n;
    int num = 1;
    scanf("%d", &n);
    int ch[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            ch[j][i] = num++;
        }
        for (int k = i-1; k >= 0; k--) {
            ch[i][k] = num++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            printf("%d ", ch[i][j]);
        }
        printf("%d\n", ch[i][n-1]);
    }
}