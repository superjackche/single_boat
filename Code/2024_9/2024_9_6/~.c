#include <stdio.h>
int main()
{
    int a = 0;
    printf("%d\n", ~a);//~表示按（二进制）位取反，0的二进制是0000 0000，按位取反后为1111 1111
    return 0;
}