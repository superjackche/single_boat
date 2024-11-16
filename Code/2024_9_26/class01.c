#include <stdio.h>
int main()
{
    int a;
    float f;
    int b;
    scanf("%d %f %d", &a, &f, &b);
    printf("%d%d\n%d %d\n%.2f %d %d", a, b, b, a, f, a, b);
    return 0;
}