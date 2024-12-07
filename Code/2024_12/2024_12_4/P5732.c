#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);
    int ch[100] = {0}; // 根据需要调整数组大小

    ch[0] = 1; // 第一行的第一个数字为1

    for (int i = 0; i < n; i++) {
        // 输出当前行
        for (int j = 0; j <= i; j++) {
            printf("%d", ch[j]);
            if (j != i) {
                printf(" ");
            }
        }
        printf("\n");

        // 从后向前更新数组，计算下一行的值
        for (int j = i + 1; j > 0; j--) {
            ch[j] = ch[j] + ch[j - 1];
        }
        //此处根本没有改变ch[0]的值，ch[0]从始至终一直是1
    }

    return 0;
}