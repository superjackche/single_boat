#include <stdio.h>
int main() {
    double s;
    double sum = 0;
    double length = 2.000000;
    int ans = 0;
    scanf("%lf", &s);
    while (sum < s) {
        sum += length;
        length *= 0.98;
        ans++;
    }
    printf("%d", ans);
}