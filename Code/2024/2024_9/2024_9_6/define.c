#include <stdio.h>
#define K(X,Y)    ((X)+(Y))
int main()
{
    int a=0, b=0, c=0;
    scanf("%d %d %d", &a, &b, &c);
    printf("%d\n", c*K(a,b));
    return 0;
}