#include <stdio.h>
int main()
{
    char ch[5] = {'a', 'b', 'c'};//不完全初始化，剩余的默认为0
    int i = 0;
    while(i < 5)
    {
        printf("%c\n", ch[i]);
        i++;
    }

    return 0;
}