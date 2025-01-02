#include <stdio.h>

int is_leapyear(int n) {
    if ((n % 4 == 0 && n % 100 != 0) || (n % 400 == 0)) return 1;
    else return -1;
}

int main () {
    int x, y;
    scanf("%d %d", &x, &y);
    int year[500] = {0};
    int num = 0;

    for (int i = x; i <= y; i++) {
        if (is_leapyear(i) > 0) {
            year[num++] = i;
        }
    }

    printf("%d\n", num);
    for (int i = 0; i < num; i++) {
        printf("%d ", year[i]);
    }
}