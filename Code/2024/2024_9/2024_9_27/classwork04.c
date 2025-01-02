#include <stdio.h>
int main()
{
    double r;
    double PI = 3.14159265;
    scanf("%lf", &r);
    printf("The perimeter is %.4lf, the area is %.4lf.", PI*r*2.0, PI*r*r);
    return 0;
}