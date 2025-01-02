#include <stdio.h>
int main() {
    int m = 0, n = 0;
    int num;

    int min = 9999;
    
    while (scanf("%d", &num), num != -1) {
        int k = 0;
        int num0 = num;
        int m0, n0;
        m = num/8;
        n = num/6;
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                int sum = 0;
                if (i*8 + j*6 == num) {
                    sum = i+j;
                    k = 1;
                            if (sum<min) {
                                m0 = i;
                                n0 = j;
                                min = sum;
                            }
                }
            }
        }
        if (k != 0) {
            printf("%d %d\n", m0, n0);
        } else {
            printf("-1\n");
        }
    }
}