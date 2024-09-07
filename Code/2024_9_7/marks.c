#include <stdio.h>
int main()
{
    int a, b, c;
    double d;
    scanf("%lf %lf %lf", &a, &b, &c);
    d = a*0.2 + b*0.3 + c*0.5;
    printf("%lf", d);
    return 0;
}