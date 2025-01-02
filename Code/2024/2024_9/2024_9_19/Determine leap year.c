#include <stdio.h>
int main()
{
    int year;
    int remainder4, remainder100, remainder400;

    printf("enter a year\n");
    scanf("%d", &year);

    remainder4 = year % 4;
    remainder100 = year % 100;
    remainder400 = year % 400;

    if((remainder4 == 0 && remainder100 != 0) || remainder400 == 0)
    printf("yes,it's a leap year.");
    else
    printf("no,it isn't.");

    return 0;
}