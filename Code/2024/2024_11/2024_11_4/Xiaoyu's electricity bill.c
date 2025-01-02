#include <stdio.h>
int main(){
    double n = 0;
    double money = 0;
    scanf("%lf", &n);
    if (n <= 150) {
        money = n * 0.4463;
    } else if (n > 150 && n <= 400) {
        money = 150 * 0.4463 + (n - 150) * 0.4663;
    } else {
        money = 150 * 0.4463 + 250 * 0.4663 + (n - 400) * 0.5663;
    }
    printf("%.1lf", money);
    return 0;
}