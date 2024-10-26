#include <stdio.h>
#include <math.h>

int main()
{
    double h, r;
    scanf("%lf %lf", &h, &r);
    double result = 20000/(3.14*r*r*h);
    int k = trunc(ceil(result));
    printf("%d", k);
    return 0;
}