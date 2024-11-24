#include <stdio.h>
int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m, k, p;
        scanf("%d %d %d %d", &n, &m, &k, &p);
        if (n*m < p+k || k > m) printf("Divide\n");
        else
        {
            if (p/n + k <= m) printf("Together\n");
            else printf("Chance\n");
        }
    }
}