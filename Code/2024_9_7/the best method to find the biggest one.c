#include <stdio.h>

int main()
{
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    int sum=(a>b?a:b)>(b>c?b:c)?(a>b?a:b):(b>c?b:c);
    printf("%d",sum);
}