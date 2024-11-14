#include <stdio.h>
int main() {
    int n;
    int ch1[1024] = {0};
    int ch2[1024] = {0};
    int ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ch1[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &ch2[i]);
    }
    for (int i = 0; i < n; i++) {
        ans += ch1[i]*ch2[i];
    }
    printf("%d", ans);
    return 0;
}