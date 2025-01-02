#include <stdio.h>

int max(int m, int n) {
    return m > n ? m : n;
}
int main() {
    int type, a, b, c, d;
    scanf("%d %d %d %d %d", &type, &a, &b, &c, &d);
    if (type == 0) {
        printf("%d", a+b);
    } else if (type == 1) {
        printf("%d", max(a-c, 0) + max(b-d, 0));
    }
}