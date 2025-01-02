#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int matrix[101][101] = {0};

    int num = 1;
    for (int sum = 0; sum <= 2 * n - 2; sum++) {    //sum表示横纵下角标之和，规律是从0到2n-2递增
        if (sum % 2 == 0) {    //偶数情况，从左下到右上
            for (int i = 0; i <= sum; i++) {
                int x = i;  //从左下到右上，x递增从零0始
                int y = sum - i;    //直接把y表示为sum-i
                if (x < n && y < n) {   //判断是否越界
                    matrix[x][y] = num++;   //先赋值再自增
                }
            }
        } else {    //奇数情况，从右上到左下
            for (int i = 0; i <= sum; i++) {
                int x = sum - i;    //从右上到左下，x递减从sum开始
                int y = i;  //直接把y表示为i
                if (x < n && y < n) {   //判断是否越界
                    matrix[x][y] = num++;   //先赋值再自增
                }
            }
        }   //sum统一自增
    }

    // 输出矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", matrix[i][j]);
            if (j < n - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}