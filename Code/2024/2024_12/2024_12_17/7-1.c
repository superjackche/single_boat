#include <stdio.h>

void bubble_sort(int *ch, int n) {  //未优化
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (ch[j] > ch[j+1]) {
                int temp = ch[j];
                ch[j] = ch[j+1];
                ch[j+1] = temp;
            }
        }
    }
}
int main (void) {
    int n, i;
    int sum = 0;
    
    scanf("%d", &n);
    int *page = (int *)malloc(n*sizeof(int));
    for (i = 0; i < n; i++) {
        scanf("%d", &page[i]);
    }

    bubble_sort(page, n);

    for (i = 0; i < n; i++) {
        if (sum + page[i] <= 1000) {
            sum += page[i];
        } else break;
    }
    printf("%d", i);
    return 0;
}