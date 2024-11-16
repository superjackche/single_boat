#include <stdio.h>
#include <math.h>

int determine_length(int n) {
    int len = 0;
    while (n > 0) {
        n = n / 10;
        len++;
    }
    return len;
}

int is_isomorphic_number(int n) {
    int len = determine_length(n);
    int square = n * n;
    int suffix = square % (int)pow(10, len);
    return suffix == n;
}

int main() {
    int x = 0;
    scanf("%d", &x);
    if (x >= 1 && x <= 10000) {
        if (is_isomorphic_number(x)) {
            printf("Yes");
        } else {
            printf("No");
        }
    } else {
        printf("%d out of range\n", x);
    }
    return 0;
}