#include <stdio.h>
int main()
{
    int n, k = 1, i = 1;
    scanf("%d", &n);
    for(i = 1; i <= n; i++)
    {
        k *= i;//k = k * i;
    }
    printf("%d", k);
    return 0; 
}