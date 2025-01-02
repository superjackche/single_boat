#include <stdio.h>
int main() {
    int n;
    int ch[1001];
    
    int ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ch[i]);
    }
    for (int j = 0; j < n; j++) {
        int judge = 1;
        for (int k = j+1; k < n; k++) {
            if (ch[j] <= ch[k]) {
                judge = 0;
                break;
            }
        }
        if (judge == 1) ans++;
    }
    printf("%d", ans);
}