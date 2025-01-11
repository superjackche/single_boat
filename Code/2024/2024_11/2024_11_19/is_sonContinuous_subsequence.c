#include <stdio.h>
#include <string.h>

int main() {
    int A[1000], B[1000];
    int i = 0, j = 0;

    // 读取序列A
    while (1) {
        scanf("%d", &A[i]);
        if (A[i] == -1) break;
        i++;
    }

    // 读取序列B
    while (1) {
        scanf("%d", &B[j]);
        if (B[j] == -1) break;
        j++;
    }

    // 检查B是否是A的连续子序列
    for (int a = 0; a <= i - j; a++) {
        int k = 0;
        for (int b = 0; b < j; b++) {
            if (A[a + b] == B[b]) {
                k++;
            } else {
                break;
            }
        }
        if (k == j) {
            printf("ListB is the sub sequence of ListA.\n");
            return 0;
        }
    }

    printf("ListB is not the sub sequence of ListA.\n");
    return 0;
}