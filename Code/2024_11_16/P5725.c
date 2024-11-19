#include <stdio.h>
int main() {
    int n = 0;
    scanf("%d", &n);
    int k = n*n;
    int m = n*(n+1)/2;
    for (int i = 1; i <= k; i++) {
        printf("%02d", i);
        if (i % n == 0) printf(" \n");
    }
    int y = 1;
    printf("\n");
    for (int j = 1; j <= n; j++) {
        for (int a = n-j; a > 0; a--) {
            printf("  ");
        }
        for (int b = 1; b <= j; b++) {
            printf("%02d", y);
            y++;
        } printf(" \n");
    }
}