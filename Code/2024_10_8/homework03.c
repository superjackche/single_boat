#include <stdio.h>
int main()
{
    double a, b, c, d;
    double k = 0.000001;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    if ((b * c - d) <= k && (b * c - d) >= -k)
        printf("error");
    else
        printf("%.1lf", a / ( b * c - d ));
    return 0;
}