#include <stdio.h>
int main()
{
    int ch = 0;
    while ((ch = getchar()) != EOF)//ctrl+z to exit,读取结束
    {
        putchar(ch);
    }
    return 0;
}