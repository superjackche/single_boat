#include <stdio.h>
int main(void)
{
    int num = 0, sum = 0;
    int n, m6, m8;
    
    while (scanf("%d", &n), n != -1)
    {
        int min = n, sign = 0;
        int a = n/6;
        int b = n/8;
        for (int i = 0; i <= a+1; i++)
        {
            for (int j = 0; j <= b+1; j++)
            {
                if (i*6 + j*8 == n)
                {
                    num = i + j;
                    if (num < min)
                    {
                        min = num;
                        m6 = i;
                        m8 = j;
                        sign = 1;
                    }
                }
            }
        }
        if (sign == 1) printf("%d %d\n", m8, m6);
        else printf("-1\n");
    }
    return 0;
}