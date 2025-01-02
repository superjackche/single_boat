#include <stdio.h>

int main(void)
{
    int n, num;
    int ch[100] = {0};
    int ans[10] = {0};
    scanf("%d", &n);
    for (int i = 1; i <= 7; i++)
    {
        scanf("%d", &num);
        ch[num] = 1;
    }
    for (int j = 0; j < n; j++)
    {
        int count = 0;
        for (int k = 1; k <= 7; k++)
        {
            scanf("%d", &num);
            if (ch[num] == 1) count++;
        }
        ans[count]++;
    }

    for (int m = 7; m > 0; m--)
    {
        printf("%d ", ans[m]);
    }

    return 0;
}