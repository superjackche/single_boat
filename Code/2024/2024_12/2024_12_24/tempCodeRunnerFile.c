#include <stdio.h>

int find_bed(int *used, int n) {
    int k = 0;
    for(k = n; k <= 3000; k++) {
        for(int i = 0; i < k; i++) {
            used[i] = 0;
        }

        for(int i = 0; i < n; i++) {
            int bed = a[i] % k;
            if(used[bed] == 1) {
                break;
            }
            used[bed] = 1; // 标记床号为已占用
        }

        return k;
    }
}
int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int used[3001];
    
    int k = find_bed(used, n);

    printf("%d", k);
    return 0;
}