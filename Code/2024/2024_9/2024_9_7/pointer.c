#include <stdio.h>
int main()
{
    int a = 10;
    int *pa = &a;
    *pa = 100;//* 解引用操作 *pa就是通过pa里面的地址找到a
    printf("a = %d\n", a);
}