#include <stdio.h>
int main() {
    int n;
    int max = 0;
    int num = 0;
    int ans = 0;
    int k, d, a;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d/%d/%d", &k, &d, &a);
        if (k - d >= 10) {
            num = k * (k - d) + a;
        } else if (k >= d) {
            num = (k - d + 1) * 3 + a;
        } else {
            num = a * 2;
        }
        if (num > max) {
            max = num;
            ans = i + 1;
        }
    }
    printf("%d", ans);
}