#include <stdio.h>
int main()
{
    int a = 0, b = 0;
    printf("please input two numbers:\n");
    scanf("%d %d",&a, &b);
    //printf("the greatest common divisor of %d and %d is: %d\n", a, b, gcd(a, b));
    //24 36
    int min = a > b ? b : a;
    while(1)
    {
        if(min % a == 0 && min % b == 0)
        {
            printf("the greatest common divisor of %d and %d is: %d\n", a, b, min);
            break;
        }
        else min--;//有问题，还没解决
    }

    return 0;
}