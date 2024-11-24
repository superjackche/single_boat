#include <stdio.h>
int main(void)
{
    int w, x, h;
    int q;
    int sum = 0;
    int cube[21][21][21] = {0};

    scanf("%d %d %d", &w, &x, &h);
    scanf("%d", &q);

    //initialize cube
    for (int i = 1; i <= w; i++)
    {
        for (int j = 1; j <= x; j++)
        {
            for (int k = 1; k <= h; k++)
            {
                cube[i][j][k] = 1;
            }
        }
    }
    
    //kill cube
    while (q--)
    {
        int x1, x2, y1, y2, z1, z2;
        scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
            {
                for (int k = z1; k <= z2; k++)
                {
                    cube[i][j][k] = 0;
                }
            }
        }
    }

    //sum cube
    for (int i = 1; i <= w; i++)
    {
        for (int j = 1; j <= x; j++)
        {
            for (int k = 1; k <= h; k++)
            {
                if (cube[i][j][k] == 1) sum++;
            }
        }
    }

    //printf sum
    printf("%d", sum);

    return 0;
}