#include <stdio.h>
int main()
{
    float t;
    int n;
    scanf("%f %d", &t, &n);
    printf("%.03f\n%d", t / n, n*2);
    return 0;
}