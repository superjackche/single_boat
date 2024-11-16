#include <stdio.h>
int Add(int a, int b)
{
    int c = a + b;
    return c;
}

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    printf("please enter two numbers which you want to add:");
    scanf("%d %d", &a, &b);
    c = Add(a, b);
    printf("the sum of %d and %d is %d", a, b, c);
    return 0;
}