#include <stdio.h>
#include <math.h>
int main()
{
    int a, b, c;
    double s, area;
    scanf("%d %d %d", &a, &b, &c);
    if (a < b + c && b < a + c && c < a + b)
    {
        s = (a + b + c) / 2.000000;
        area = sqrt(s * (s - a) * (s - b) * (s - c));
        printf("%.3f", area);
    }
    else
    {
    printf("The edges cannot make up of a triangle.");
    }
    return 0;
}