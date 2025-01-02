#include <stdio.h>
#include <math.h>

int main (void)
{
    int n;
    int max = 0;
    int ch[2000000] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        double a = 0;
        int b = 0;
        scanf("%lf %d", &a, &b);
        for (int j = 1; j <= b; j++)
        {
            int k = floor(a*j);
            if (k > max) max = k;
            if (ch[k] == 0) ch[k] = 1;
            else ch[k] = 0;
        }
    }

    for (int j = 1; j <= max; j++)
    {
        if (ch[j] == 1) printf("%d", j);
    }
}