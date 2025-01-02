#include <stdio.h>

#define MAX_N 101

// 交换两行
void swap_rows(int matrix[][MAX_N], int row1, int row2, int n) {
    for (int i = 0; i < n; ++i) {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

// 冒泡排序
void bubble_sort(int matrix[][MAX_N], double averages[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (averages[j] > averages[j + 1]) {
                // 交换平均值
                double temp_avg = averages[j];
                averages[j] = averages[j + 1];
                averages[j + 1] = temp_avg;

                // 交换行
                swap_rows(matrix, j, j + 1, n);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int matrix[MAX_N][MAX_N];
    double averages[MAX_N];

    // 读取矩阵并计算每行的平均值
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
            averages[i] += matrix[i][j];
        }
        averages[i] /= n*1.0;
    }

    // 使用冒泡排序
    bubble_sort(matrix, averages, n);

    // 输出排序后的矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d", matrix[i][j]);
            if (j < n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}