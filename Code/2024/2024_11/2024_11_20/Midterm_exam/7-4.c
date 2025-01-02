#include <stdio.h>

int main(void)
{
    int sum = 0;
    int num = 0;
    int sign = 0;
    int all = 0;
    int c;
    while ((c = getchar()) != EOF && c!= '\n')
    {
        if (c >= '0' && c <= '9')
        {
            num = c - '0';
            sum = num + sum*10;
            sign = 1;
        }
        else
        {
            sign = 0;
            all += sum;
            num = 0;
            sum = 0;
        }
    }
    if (sign)
    {
        all += sum;
    }
    printf("%d", all);
    return 0;
}