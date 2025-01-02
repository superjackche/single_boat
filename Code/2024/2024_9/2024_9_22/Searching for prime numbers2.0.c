#include <stdio.h>
#include <math.h>
int main()
{
    int i;
    int j;
    int key = 1;

    for (i = 3; i <= 1000000; i += 2)
    {
        for (j = 2; j <= (int)sqrt(i); j++)//sqrt(i)是开方的i
        {
            if (i % j == 0)
            {
                key = 0;
                break;
            }
        }
        if (key == 1)
        {
            printf("%d  ", i);
        }    
    }

    return 0;
}