#include <stdio.h>
int main (void)
{
    int matrix[102][102] = {0};
    int n, m, key;
    int x, y;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        int min = 9999999;
        int max = -9999999;
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] > max)
            {
                max = matrix[i][j];
                x = i;
                y = j;
            }
        }
        for (int k = 0; k < n; k++)
        {
            if (matrix[k][y] < min)
            {
                min = matrix[k][y];
                key = k;
            }
        }
        if (key == x)
        {
            printf("The saddle point is (%d,%d)=%d.", x, y, matrix[x][y]);
            return 0;
        }
    }
    printf("There is no saddle point in the matrix.");

    return 0;
}