#include <stdio.h>\

int main() {
    int height[1024] = {0};
    int n, m;
    int l, r, k;
    char op[6];
    scanf("%d %d", &n, &m);
    while (m--) {
        scanf("%s", &op);
        if(op[0]=='w') {
            scanf("%d %d", &l, &r);
            for (int i = l; i <= r; i++) {
                height[i]++;

            }
        } else if (op[0]=='r') {
            int num = 0;
            scanf("%d %d %d", &l, &r, &k);
            for (int i = l; i <= r; i++) {
                if (height[i] >= k) {
                    height[i] = 0;
                    num++;
                }
            }
            printf("%d\n", num);
        }
    }
}