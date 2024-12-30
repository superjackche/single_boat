#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1024

// 递归函数，标记赦免状态
void mark_forgiveness(int matrix[][MAX_SIZE], int n, int size, int x, int y) {
    if (size == 1) {
        // 基本情况：子矩阵大小为1x1，无需进一步划分
        return;
    }

    int half = size / 2;

    // 标记左上角子矩阵为赦免（0）
    for(int i = x; i < x + half; i++) {
        for(int j = y; j < y + half; j++) {
            matrix[i][j] = 0;
        }
    }

    // 标记其他三个子矩阵为不赦免（1）
    // 右上角
    for(int i = x; i < x + half; i++) {
        for(int j = y + half; j < y + size; j++) {
            matrix[i][j] = 1;
        }
    }
    
    // 左下角
    for(int i = x + half; i < x + size; i++) {
        for(int j = y; j < y + half; j++) {
            matrix[i][j] = 1;
        }
    }
    
    // 右下角
    for(int i = x + half; i < x + size; i++) {
        for(int j = y + half; j < y + size; j++) {
            matrix[i][j] = 1;
        }
    }

    // 递归处理不赦免的三个子矩阵
    // 右上角
    mark_forgiveness(matrix, n, half, x, y + half);
    // 左下角
    mark_forgiveness(matrix, n, half, x + half, y);
    // 右下角
    mark_forgiveness(matrix, n, half, x + half, y + half);
}

int main(){
    int n;
    scanf("%d", &n);
    int size = pow(2, n);

    int matrix[size][MAX_SIZE];

    // 初始化整个矩阵为1（未赦免）
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            matrix[i][j] = 1;
        }
    }

    // 开始递归标记赦免状态
    mark_forgiveness(matrix, n, size, 0, 0);

    // 输出结果
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%d", matrix[i][j]);
            if(j != size - 1){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}