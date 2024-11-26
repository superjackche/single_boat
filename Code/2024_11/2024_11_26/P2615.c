#include <stdio.h>
int main(void)
{
    int n;
    int ch[40][40] = {0};
    scanf("%d", &n);
    int n2 = n*n;
    int x, y;
    
    ch[0][n/2] = 1;
    x = 0, y = n/2;

    for (int i = 1; i < n2; i++)
    {
        if (x == 0 && y != n-1)
        {
            x = n-1, y += 1;
            ch[x][y] = i+1;
        }
        else if (x != 0 && y == n-1)
        {
            x -= 1, y = 0;
            ch[x][y] = i+1;
        }
        else if (x == 0 && y == n-1)
        {
            x += 1;
            ch[x][y] = i+1;
        }
        else
        {
            if (ch[x-1][y+1] == 0)
            {
                x -= 1, y += 1;
                ch[x][y] = i+1;
                continue;
            }
            else if (ch[x+1][y] == 0)
            {
                x += 1;
                ch[x][y] = i+1;
            }
        }
    }

    for (int a = 0; a < n; a++)
    {
        for (int b = 0; b < n; b++)
        {
            printf("%d ", ch[a][b]);
        }
        printf("\n");
    }
}