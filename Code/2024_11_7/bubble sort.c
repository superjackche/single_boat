#include <stdio.h>

// 设计一个从小到大排序的冒泡排序
void bubble_sort(int arr[], int sz) {
    for (int i = 0; i < sz - 1; i++) {
        for (int j = 0; j < sz - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[10];
    int sz = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < sz; i++) {
        scanf("%d", &arr[i]);
    }

    bubble_sort(arr, sz);
    return 0;
}