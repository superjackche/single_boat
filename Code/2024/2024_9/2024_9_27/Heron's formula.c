#include <stdio.h>
#include <math.h>
int main()
{
    double a, b, c;
    double p = 0;
    double s = 0;
    scanf("%lf %lf %lf", &a, &b, &c);
    p = (a + b + c) / 2.0;
    if(p > 0 && p > a && p > b && p > c)
    {
        s = sqrt(p * (p - a) * (p - b) * (p - c));
        printf("%.1lf", s);
    }
    return 0;
}