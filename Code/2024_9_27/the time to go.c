#include <stdio.h>
int main()
{
    int s, v, time1, time2;
    scanf("%d %d", &s, &v);
    time1 = (480 - (s / v + 10)) / 60;
    time2 = (480 - (s / v + 10)) % 60;
    printf("%d:%d", time1, time2);
    return 0;
}