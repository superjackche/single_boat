#include <stdio.h>
int main()
{
    int a, b = 0;
    int Max = 0;
    scanf("%d", &a);
    scanf("%d", &b);
    /*if (a > b)
        Max = a;
    else if (a < b)
        Max = b;
    else
        Max = a;*/  
    Max = a > b ? a : b;
    printf("the biggest num is %d\n", Max);
    return 0;
}