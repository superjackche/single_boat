#include <stdio.h>
int main (void)
{
    int n;
    scanf("%d", &n);
    int ans[11][11] = {0};

    //右下左上
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    int x = 0, y = 0;

    int n2 = n*n;
    int num = 1;
    int sign = 0;

    while (num <= n2)
    {
        ans[x][y] = num;
        num++;

        int nx = x + dx[sign];
        int ny = y + dy[sign];

        if (nx < 0 || ny < 0 || nx >= n || ny >= n || ans[nx][ny] != 0)
        {
            sign = (sign + 1) % 4;
            nx = x + dx[sign];
            ny = y + dy[sign];
        }

        x = nx;
        y = ny;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (ans[i][j] < 10)
            {
                printf("  %d", ans[i][j]);
            }
            else
            {
                printf(" %d", ans[i][j]);
            }
        }
        printf("\n");
    }
}