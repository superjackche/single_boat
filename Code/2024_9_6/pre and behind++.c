#include <stdio.h>
int main()
{
    int a = 10;
    int b = ++a;
    int c = a++;
    printf("%d %d %d", a, b, c);

    return 0;
}