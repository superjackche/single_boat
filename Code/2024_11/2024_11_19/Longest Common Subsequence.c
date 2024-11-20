#include <stdio.h>

int main(void)
{
    int ch[1024] = {0};
    int n;
    int num = 0;
    int max = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ch[i]);
    }

    for (int i = 0; i < n; i++)
    {
        if (ch[i] == ch[i+1])
        {
            num++;
            if (num > max) max = num;
        }
        else
        {
            num = 0;
        }
    }

    printf("%d", max+1);
    return 0;
}