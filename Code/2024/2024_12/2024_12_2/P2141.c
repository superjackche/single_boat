#include <stdio.h>

int main (void)
{
    int n;
    int ch[102] = {0};
    long sum = 0;
    int ans[102] = {0};
    int num = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ch[i]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                for (int k = 0; k < n; k++)
                {
                    if (j != k && i != k)
                    {
                        if (ch[i] == ch[j] + ch[k])
                        ans[i] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (ans[i] == 1) num++;
    }
    printf("%d", num);

}