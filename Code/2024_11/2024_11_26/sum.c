#include <stdio.h>
int main(void)
{
    int ch[12][12] = {0};
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &ch[j][i]);
        }
    }

    int x, y;
    int sum = 0;
    scanf("%d %d", &x, &y);

    for (int i = x-1; i <= x+1; i++)
    {
        for (int j = y-1; j <= y+1; j++)
        {
            sum += ch[j][i];
        }
    }
    sum -= ch[y][x];
    printf("%d", sum);
}