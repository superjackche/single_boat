#include <stdio.h>
int main(){
    int a = 0, b = 0, c = 0;
    int max, mid, min;
    scanf("%d%d%d", &a, &b, &c);
    if (a >= b) {
        if (a >= c) {
            max = a;
            if (b >= c) {
                mid = b, min = c;
            } else {
                mid = c, min = b;
            }
        } else {
            max = c, mid = a, min = b;
        }
    } else {
        if (b >= c) {
            max = b;
            if (a >= c) {
                mid = a, min = c;
            } else {
                mid = c, min = a;
            }
        } else {
            max = c, mid = b, min = a;
        }
    }

    printf("%d %d %d", min, mid, max);
    return 0;
}