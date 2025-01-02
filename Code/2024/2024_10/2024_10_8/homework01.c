#include <stdio.h>
int main()
{
    int a, b, max, min;
    scanf("%d %d", &a, &b);
    if (a == b)
    {
            printf("The two numbers are equal.");
    }
    else{
        if (a > b)
        {
            max = a;
            min = b;
        }
        else
        {
            max = b;
            min = a;
        }
    printf("The larger number is %d, the smaller number is %d.", max, min);
        }
    return 0;
}