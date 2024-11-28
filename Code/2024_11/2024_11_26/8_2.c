#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    float sales[6][5] = {0};

    for (int i = 0; i < n; i++) {
        int salesman, product;
        float amount;
        scanf("%d %d %f", &salesman, &product, &amount);
        sales[product - 1][salesman - 1] += amount;
    }

    // 计算每行的总和
    for (int i = 0; i < 5; i++) {
        float row_sum = 0;
        for (int j = 0; j < 4; j++) {
            row_sum += sales[i][j];
        }
        sales[i][4] = row_sum;
    }

    // 计算每列的总和
    for (int j = 0; j < 4; j++) {
        float col_sum = 0;
        for (int i = 0; i < 5; i++) {
            col_sum += sales[i][j];
        }
        sales[5][j] = col_sum;
    }

    // 计算总和
    float total_sum = 0;
    for (int j = 0; j < 4; j++) {
        total_sum += sales[5][j];
    }
    sales[5][4] = total_sum;

    // 打印结果矩阵
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%.1f", sales[i][j]);
            if (j < 4) {
                printf("\t");
            }
        }
        printf("\n");
    }

    return 0;
}