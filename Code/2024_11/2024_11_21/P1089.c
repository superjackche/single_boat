#include <stdio.h>
int main(void)
{
    int m[12] = {0};
    int save = 0;

    for (int i = 0; i < 12; i++)
    {
        scanf("%d", &m[i]);
    }

    int re = 0;
    for (int j = 0; j < 12; j++)
    {
        re += 300 - m[j];
        if (re < 0)
        {
            printf("-%d", j+1);
            return 0;
        }
        if (re >= 100)
        {
            save += re / 100;
            re %= 100;
        }
    }
    printf("%d", save*120 + re);
}