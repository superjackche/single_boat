#include <stdio.h>
int main() {
    int n = 0;
    scanf("%d", &n);
    long long num = 1;
    for (int i = 1; i < n; i++) {
        num = (num + 1) * 2;
    }
    printf("%lld", num);
}