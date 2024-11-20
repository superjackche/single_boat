#include <stdio.h>

int main(void) {
    int n, d, m;
    scanf("%d %d %d", &n, &d, &m);

    // 遍历所有可能的第2站上车人数
    for(int in2 = 0; in2 <= m; in2++) {
        int peo = d;          // 当前车上人数，初始化为第1站上车人数
        int prev2 = d;        // 前两站的上车人数（第1站）
        int prev1 = in2;      // 前一站的上车人数（第2站）

        // 模拟从第3站到第n-1站的情况
        for(int i = 3; i < n; i++) {
            int current_in = prev1 + prev2; // 当前站上车人数
            peo += prev2;                   // 更新车上人数
            prev2 = prev1;                  // 更新前两站上车人数
            prev1 = current_in;             // 更新前一站上车人数
        }

        // 检查是否满足最后一站下车人数为m
        if(peo == m) {
            printf("%d\n", in2);
            return 0;
        }
    }

    return 0;
}