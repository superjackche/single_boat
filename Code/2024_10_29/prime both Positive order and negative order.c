#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int turn_upside_down(int n) {
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n = n / 10;
    }
    return reversed;
}

int main(){
    for (int i = 1; i <= 9999; i++) {
        if (is_prime(i) == 1 && is_prime(turn_upside_down(i)) == 1) {
            printf("%d\n", i);
        }
    }
    return 0;
}