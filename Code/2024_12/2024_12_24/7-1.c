#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long k;
    int used[3001];
    for(k = n; k <= 3000; k++) {
        for(int i = 0; i < k; i++) {
            used[i] = 0;
        }

        int sign = 0;
        for(int i = 0; i < n; i++) {
            int bed = a[i] % k;
            if(used[bed] == 1) {
                sign = 1;
                break;
            }
            used[bed] = 1; // 标记床号为已占用
        }

        if(sign == 0) { // 找到满足条件的最小k
            printf("%ld", k);
            return 0;
        }
    }

    return 0;
}