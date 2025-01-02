#include <stdio.h>

int main() {
    int k = 0;
    int n = 1;
    int endings = 1;
    scanf("%d", &k);
    double sn1 = 1.0 / n;
    while (endings) {
        if (sn1 > k) {
            printf("%d", n);
            endings = 0;
        } else {
            n++;
            sn1 += 1.0 / n;
        }
    }
    
    return 0;
}