#include <stdio.h>
int main (void)
{
    int n, m;
    int ch[3001] = {0};
    int min = 99999;
    
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ch[i]);
    }

    for (int j = 0; j <= n-m; j++)
    {
        int sum = 0;
        for (int k = 0; k < m; k++)
        {
            sum += ch[j+k];
        }
        if (sum < min) min = sum;
    }

    printf("%d", min);
}