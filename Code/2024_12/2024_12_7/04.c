#include <stdio.h>

void de(int *ch, int n, int num)
{
    for (int j = 0; j < n; j++)
    {
        if (ch[j] + ch[n-1] < num) continue;
        for (int k = 1; k < n-j; k++)
        {
            if (ch[j] + ch[j+k] > num) break;
            if (ch[j] + ch[j+k] == num)
            {
                printf("%d = %d + %d\n", num, ch[j], ch[j+k]);
                return;
            }
        }
        
    }
}

int main()
{
    int n, m;
    scanf("%d", &n);
    int ch[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ch[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int num;
        scanf("%d", &num);
        de(ch, n, num);
    }
}