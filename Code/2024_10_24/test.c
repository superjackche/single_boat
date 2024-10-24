#include <stdio.h>

int main(){
    int n;
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    while (scanf("%d", &n) != -1) {
            if (n > 0) {
                a++;
                d += n;
            } else if (n == 0) {
                b++;
            } else if (n < 0) {
                c++;
                e += n;
            } scanf("%d", &n);   
    }
    printf("%d %d %d\n%d %d", a, b, c, d, e);
}