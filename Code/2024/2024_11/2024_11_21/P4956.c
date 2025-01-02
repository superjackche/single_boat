#include <stdio.h>

int main(void)
{
    int sum = 0 ,temp = 0;
    int need;
    int ans1 = 0, ans2 = 0;
    scanf("%d", &need);
    need /= 364;
    for (int k = 1; k > 0; k++)
    {
        for (int x = 1; x <= 100; x++)
        {
            sum = (x + 3*k);
            if (sum == need)
            {
                ans1 = x;
                ans2 = k;
                printf("%d\n%d\n", ans1, ans2);
                return 0;
            }
        }
    }
    
}