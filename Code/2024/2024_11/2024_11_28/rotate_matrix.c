#include <stdio.h>

int main(void) {
    int n;
    int m = 1;
    scanf("%d", &n);
    int k1 = n * n;
    int snake[101][101] = {0};

    int dx[] = {0, 1, 0, -1}; // 向右、向下、向左、向上
    int dy[] = {1, 0, -1, 0}; // 向右、向下、向左、向上
    int x = 0, y = 0; // 初始位置
    int dir = 0; // 初始方向为向右
    int num = 1; // 当前填充的数字

    while (num <= k1) {
        snake[x][y] = num++;

        // 计算下一个位置
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // 检查是否越界或已经填充过
        if (nx < 0 || nx >= n || ny < 0 || ny >= n || snake[nx][ny] != 0) {
            // 改变方向
            dir = (dir + 1) % 4;
            nx = x + dx[dir];
            ny = y + dy[dir];
        }

        x = nx;
        y = ny;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            printf("%d ", snake[i][j]);
        }
        printf("%d\n", snake[i][n-1]);
    }

    return 0;
}