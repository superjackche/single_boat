#include <stdio.h>
int main()
{
    char m[1];
    int age;
    float height;
    scanf("%s %d %f", m, &age, &height);
    printf("The sex is %s, the age is %d, and the height is %f.", m, age, height);
    return 0;
}