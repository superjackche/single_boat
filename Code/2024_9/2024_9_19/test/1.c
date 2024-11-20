#include <stdio.h>
int main()
{
    int n, m, k, Max;
    scanf("%d", &n);
    while(scanf("%d", &m) != EOF)
    {
        for(n = 1; n <= m; n++)
    {
        for(k = 2; k <= m; k++)
        {
            if(n % k == 0)
                break;
        }
        if(n == k)
            Max = k;  
    }
    printf("%d ", Max);
    }
    return 0;
}