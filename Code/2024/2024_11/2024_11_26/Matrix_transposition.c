#include <stdio.h>
int main(void)
{
    int m, n;
    int ch[1024][1024] = {0};

    //scanf
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &ch[i][j]);
        }
    }

    //transform
    for (int p = 0; p < n; p++)
    {
        for (int q = 0; q < m-1; q++)
        {
            printf("%d ", ch[q][p]);
        }
        printf("%d\n", ch[m-1][p]);
    }
}