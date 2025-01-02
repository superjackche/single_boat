#include <stdio.h>
int main (void)
{
    int n, m, k;
    int count = 0;
    scanf("%d %d %d", &n, &m, &k);
    int place[n+5][n+5];    //防止数组越界
    int x, y;
    for (int i = 3; i < n+3; i++)
    {
        for (int j = 3; j < n+3; j++)
        {
            place[i][j] = 0;
        }
    }

    //torch
    while (m--)
    {
        scanf("%d %d", &x, &y);
        x += 2;
        y += 2;
        for (int i = x-2; i <= x+2; i++)
        {
            place[i][y] = 1;
        }
        for (int j = y-2; j <= y+2; j++)
        {
            place[x][j] = 1;
        }
        place[x-1][y-1] = 1;
        place[x-1][y+1] = 1;
        place[x+1][y-1] = 1;
        place[x+1][y+1] = 1;
    }

    //fluorite
    while (k--)
    {
        scanf("%d %d", &x, &y);
        x += 2;
        y += 2;
        for (int i = x-2; i <= x+2; i++)
        {
            for (int j = y-2; j <= y+2; j++)
            {
                place[i][j] = 1;
            }
        }
    }

    //exam
    for (int i = 3; i < n+3; i++)
    {
        for (int j = 3; j < n+3; j++)
        {
            if (place[i][j] == 0) count++;
        }
    }

    printf("%d", count);
}