#include <stdio.h>
#include <stdlib.h>
int k;
int fib(int n)
{
    int a=1,b=1,c=1;
    while(n>=3)
    {
        c=a+b;
        a=b;
        b=c;
        n--; 
}                           
    return c;
}
int main()
{
    int n,ret=0;
    scanf("%d", &k);
    while(scanf("%d", &n) != EOF)
    {
    ret=fib(n + 1);
    printf("%d ",ret);
    }
    return 0;
}