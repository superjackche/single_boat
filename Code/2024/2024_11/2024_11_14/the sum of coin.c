#include <stdio.h>

int howmuch_time(int n) {
    for (int i = 1;; i++) {
        if (i*(i+1)/2 > n) {
            return i-1;
        }
    }
}
int main() {
    int k = 0;
    int sum = 0;
    int times = 0;
    scanf("%d", &k);
    times = howmuch_time(k);
    for (int i = 1; i <= times; i++) {
        sum += i * i;
    }
    sum += (times+1)*(k-times*(times+1)/2);
    printf("%d", sum);

    return 0;
}