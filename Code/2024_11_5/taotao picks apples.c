#include <stdio.h>

int main() {
    int apple_heights[10]; // 存储 10 个苹果的高度
    int tao_tao_height;    // 陶陶伸手能够达到的最大高度
    int num = 0;           // 记录陶陶能够摘到的苹果数目

    // 读取 10 个苹果的高度
    for (int i = 0; i < 10; i++) {
        scanf("%d", &apple_heights[i]);
    }

    // 读取陶陶伸手能够达到的最大高度
    scanf("%d", &tao_tao_height);

    // 计算陶陶能够摘到的苹果数目
    for (int i = 0; i < 10; i++) {
        if (apple_heights[i] <= tao_tao_height + 30) { // 考虑板凳的高度
            num++;
        }
    }

    // 输出结果
    printf("%d", num);

    return 0;
}