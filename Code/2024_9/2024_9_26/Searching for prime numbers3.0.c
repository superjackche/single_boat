#include <stdio.h>
#include <math.h>
int search_prime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    int i;
    int num = 0;

    for (i = 3; i <= 1000; i += 2)
    {
        if (search_prime(i) == 1)
        printf("%d  ", i);
        num++;
    }
    printf("\n%d", num);
    return 0;
}