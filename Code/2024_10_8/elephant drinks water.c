#include <stdio.h>
char bracket_function(char* num)
{
    if (*num % 1 ==0)
    {
        return *num;
    }
    else
    {
        return(*num / 1);
    }
}
int main()
{
    int h, r, P = 3.14;
    scanf("%d %d", &h, &r);
    int size = P * r * r * h;
    int result = 20 / size + 1;
    bracket_function(result);
    printf("%d", result);
    return 0;
}