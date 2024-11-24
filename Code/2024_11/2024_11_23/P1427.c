#include <stdio.h>
int main(void)
{
    long long ch[101] = {0};
    long long temp = 0;
    int i = 0;
    while (scanf("%lld", &temp), temp != 0)
    {
        ch[i] = temp;
        i++;
    }
    for (int j = i-1; j >= 0; j--)
    {
        printf("%lld ", ch[j]);
    }
}