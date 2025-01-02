#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int arr[10000]; // 足够大的数组，避免越界
    int head = 5000, tail = 5000; 

    arr[head] = n; // 将 n 放入队列

    for (int i = n - 1; i >= 1; i--)
    {
        head--;
        arr[head] = i; // 将当前数字插入队列头部

        // 如果队列长度大于等于 3，将尾部的两个数字移到头部(下一次循环队列头部插入新数字)
        if (tail - head + 1 >= 3 && i != 1)
        {
            arr[head - 2] = arr[tail - 1]; // 将第一个元素移到第二个位置
            arr[head - 1] = arr[tail]; // 将尾部元素移到头部第二个位置
            tail -= 2;
            head -= 2;
        }
    }

    // 输出结果
    for (int i = head; i <= tail; i++) {
        printf("%d", arr[i]);
        if (i != tail) printf(" ");
    }
    printf("\n");

    return 0;
}