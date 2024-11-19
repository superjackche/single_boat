#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    int num100 = 0, num50 = 0, num20 = 0, num10 = 0, num5 = 0, num2 = 0, num1 = 0;
    while (n >= 100)
    {
        num100 = n / 100;
        n %= 100;
    }
    while (n >= 50)
    {
        num50 = n / 50;
        n %= 50;
    }
    while (n >= 20)
    {
        num20 = n / 20;
        n %= 20;
    }
    while (n >= 10)
    {
        num10 = n / 10;
        n %= 10;
    }
    while (n >= 5)
    {
        num5 = n / 5;
        n %= 5;
    }
    while (n >= 2)
    {
        num2 = n / 2;
        n %= 2;
    }
    while (n >= 1)
    {
        num1 = n / 1;
        n %= 1;
    }
    if (num100 != 0) printf("100:%d\n", num100);
    if (num50 != 0) printf("50:%d\n", num50);
    if (num20 != 0) printf("20:%d\n", num20);
    if (num10 != 0) printf("10:%d\n", num10);
    if (num5 != 0) printf("5:%d\n", num5);
    if (num2 != 0) printf("2:%d\n", num2);
    if (num1 != 0) printf("1:%d\n", num1);
    return 0;
}