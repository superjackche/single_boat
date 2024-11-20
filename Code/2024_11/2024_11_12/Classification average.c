#include <stdio.h>

int main(){
    int n = 0, k = 0;
    int sum1 = 0, sum2 = 0;
    int num1 = 0, num2 = 0;
    double ans1 = 0, ans2 = 0;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        if (i < k) {
            sum2 += i;
            num2++;
        } else {
            if (i % k == 0) {
                sum1 += i;
                num1++;
            } else {
                sum2 += i;
                num2++;
            }
        }
    }
    ans1 = (1.0 * sum1) / num1;
    ans2 = (1.0 * sum2) / num2;
    printf("%.1lf %.1lf", ans1, ans2);
    return 0;
}