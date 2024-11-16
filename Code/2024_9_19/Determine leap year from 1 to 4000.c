#include <stdio.h>
int main()
{
    int year = 1;

    for(; year <= 4000; year++)
    {
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            printf("%d  ", year);
        }
    }

    return 0;
}