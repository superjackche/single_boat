#include <stdio.h>
int main() {
    int n = 0;
    int num = 0;
    int min = 999999999;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &num);
        if (num < min) {
            min = num;
        }
    }
    printf("%d", min);
    return 0;
}