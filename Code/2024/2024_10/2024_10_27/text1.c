#include <stdio.h>
int main(){
    int c1, c2, e0, e1, x1, x2, k;
    scanf("%d%d%d", &c1, &c2, &e0);
    if (e0 <= c1) {
        x1 = x2 = e0/2.0;
    } else {
        x1 = x2 = c1/2.0;
        e1 = e0 - c1;
        if (c2 - e1 - x2 >= c1 - x1) {
            x2 = x2 + e1;
        } else {
            x2 = c2 - c1/2.0;
            k = e0 - x1 - x2;
            x1 = k/2.0 + x1;
            x2 = k/2.0 + x2;
        }
    }
    printf("%d %d", x1, x2);
    return 0;
}