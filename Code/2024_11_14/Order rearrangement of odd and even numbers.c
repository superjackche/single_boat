#include <stdio.h>
int main() {
    int n = 0;
    int num = 0;
    int a = 0, b = 0;
    int ch1[1024] = {0};
    int ch2[1024] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        if (num % 2 == 0) {
            ch1[a] = num;
            a++;
        } else {
            ch2[b] = num;
            b++;
        }
    }
    if (n == 1) {
        printf("%d\n", num);
    } else {
        if (b != 0) {
            for (int i = 0; i < a; i++) {
                printf("%d ", ch1[i]);
            }
            for (int i = 0; i < b-1; i++) {
            printf("%d ", ch2[i]);
            }
            printf("%d\n", ch2[b-1]);
        }
        if (b == 0) {
            for (int i = 0; i < a-1; i++) {
                printf("%d ", ch1[i]);
            }
            printf("%d\n", ch1[a-1]);
        }
    }
    return 0;
}