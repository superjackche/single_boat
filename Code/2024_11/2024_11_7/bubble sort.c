#include <stdio.h>

//���һ�������㷨
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ���һ����С���������ð������
void bubble_sort(int arr[], int sz) {
    int flag = 0;
    for (int i = 0; i < sz - 1; i++) {
        for (int j = 0; j < sz - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
        // ��ӡÿ������������
        for (int i = 0; i < sz; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    int arr[1024];
    int i = 0;

    while (scanf("%d", &arr[i])) {
        i++;
        if (i >= 1024 || getchar() == '\n') {
            break; // ��ֹ����Խ��
        }
    }

    bubble_sort(arr, i);
    return 0;
}