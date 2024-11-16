#include <stdio.h>

int is_prime(int n) {
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return 0;
    } return 1;
}
int main() {
    int sum = 0;
    int num = 0;
    int L = 0;
    scanf("%d", &L);
    for (int i = 2; ; i++) {
        if (is_prime(i)) {
            sum += i;
            num++;
            if (sum < L) {
                printf("%d\n", i);
            } else if (sum == L) {
                printf("%d\n%d", i, num);
                return 0;
            } else {
                printf("%d", num - 1);
                return 0;
            }
        }
    }
}