#include <stdio.h>
#include <string.h>

int main (void)
{
    char ch[999999];
    int sign = 0;
    int count0 = 0;
    int count1 = 0;
    scanf("%s", &ch[0]);
    int n = strlen(ch);
    int n2 = n*n;
    int times = 0;
    int sum = 0;
    for (int i = n; times < n-1; i += n)
    {
        scanf("%s", &ch[i]);
        times++;
    }

    printf("%d ", n);
    for (int j = 0; ; j++)
    {
        if (ch[j] == sign + '0')
        {
            if (sign == 0) count0++;
            else count1++;
        }
        else
        {
            if (sign == 0)
            {
                sum += count0;
                printf("%d ", count0);
                if (sum >= n2) return 0;
                count0 = 0;
                sign = 1;
                count1++;
            }
            else
            {
                sum += count1;
                printf("%d ", count1);
                if (sum >= n2) return 0;
                count1 = 0;
                sign = 0;
                count0++;
            }
        }
    }
}