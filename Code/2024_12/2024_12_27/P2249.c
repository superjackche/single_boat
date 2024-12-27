#include <stdio.h>

int binary_search(int *num, int n, int search) {
    int left = 0, right = n-1;
    int result = -1;
    while (left <= right) {
        int mid = (left + right)/2;
        if (num[mid] < search) {
            left = mid + 1;
        } else if (num[mid] > search) {
            right = mid - 1;
        } else {
            result = mid;
            right = mid-1;
        }
    }
    return result;    //未找到，返回-1
}

int main (){
    int n, m;
    scanf("%d %d", &n, &m);
    int num[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }

    for (int j = 0; j < m-1; j++) {
        int search;
        scanf("%d", &search);
        int sign = binary_search(num, n, search);
        if (sign != -1) printf("%d ", sign+1);
        else printf("-1 ");
    }
        int search;
        scanf("%d", &search);
        int sign = binary_search(num, n, search);
        if (sign != -1) printf("%d", sign+1);
        else printf("-1");

    return 0;
}