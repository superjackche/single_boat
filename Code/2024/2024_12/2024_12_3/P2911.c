#include <stdio.h>
#include <string.h>

int main (void)
{
    int s1, s2, s3, ans;
    int num[10000] = {0};
    int sum = 0, max = 0;
    scanf("%d %d %d", &s1, &s2, &s3);

    int ch1[s1], ch2[s2], ch3[s3];
    
    for (int i = 1; i <= s1; i++)
    {
        ch1[i] = i;
    }
    for (int i = 1; i <= s2; i++)
    {
        ch2[i] = i;
    }
    for (int i = 1; i <= s3; i++)
    {
        ch3[i] = i;
    }

    for (int i = 1; i <= s1; i++)
    {
        for (int j = 1; j <= s2; j++)
        {
            for (int k = 1; k <= s3; k++)
            {
                sum = ch1[i] + ch2[j] + ch3[k];
                num[sum]++;
            }
        }
    }

    for (int n = 0; n < 10000; n++)
    {
        if (num[n] > max)
        {
            max = num[n];
            ans = n;
        }
    }
    
    printf("%d", ans);

    return 0;
}