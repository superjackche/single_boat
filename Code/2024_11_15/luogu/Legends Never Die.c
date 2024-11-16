#include <stdio.h>
int main() {
    int a, b, c, k;
    scanf("%d %d %d %d", &a, &b, &c, &k);
    if (a+b>=k) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    if (a+c>=k) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    if (c+b>=k) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}