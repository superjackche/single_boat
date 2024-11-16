#include <stdio.h>

int main()
{
    int a = 10;
    int b = 5;
    int c = 15;
    if (a > b)
    {
        if (a > c)
        {
            printf("%d is the largest number", a);
        }
        else
        {
            printf("%d is the largest number", c);
        }
    }
    else
    {
        printf("faliure");
    }
}