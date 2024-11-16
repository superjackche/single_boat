#include <stdio.h>
void test()
{
    static  int a = 1;  //static修饰局部变量，改变了变量的生存周期（本质上是改变了变量的存储类型）
    a++;
    printf("%d\n", a);
}
int main()
{
    int i = 0;
    while (i < 10)
    {
        test();
        i++;
    }
    return 0;
}