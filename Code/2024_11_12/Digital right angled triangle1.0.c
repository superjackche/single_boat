#include <stdio.h>

int num_need(int n) {
    return n*(n+1)/2;
}

int main(){
    int n = 0;
    char num[1024];
    scanf("%d", &n);
    int k = num_need(n);
    for (int i = 1; i <= k; i++) {
        num[i] = i;
    }
    int time = 0;
    for (int i = 1; i <= k; i++) {
        if (i < 10) {
            printf("0%d", num[i]);
            time++;
        } else {
            printf("%d", num[i]);
            time++;
        }
        if (time == n) {
            printf("\n");
            n--;
            time = 0;
        }
    }
    return 0;
}