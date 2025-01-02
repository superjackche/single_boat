#include <stdio.h>

int first_biggest(long long *ch, long long n)
{
    long long ans = 0;
    for (long long i = 1; i < n; i++)
    {
        if (ch[0] < ch[i]) ans = 1;
    }
    return ans;
}

int sum(long long *ch, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += ch[i];
    }
    return sum;
}

int find_thebiggest(long long *ch, long long n)
{
    long long max = 0;
    for (long long i = 0; i < n; i++)
    {
        if (ch[i] > max) max = ch[i];
    }
    return max;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        long long ch[100001] = {0};
        long long n = 0, k = 0;

        scanf("%lld %lld", &n, &k);
        for (long long i = 0; i < n; i++)
        {
            scanf("%lld", &ch[i]);
        }

        if (n == 2 && k % 2 == 1)
        {
            printf("%lld", ch[1]*2);
        }

        if (first_biggest(ch, n) == 0)
        {
            printf("%lld\n", ch[0]*n);
        }
        else
        {
            if (k == 0) printf("%lld\n", sum(ch, n));
            else printf("%lld\n", find_thebiggest(ch, n)*n);
        }
    }
}