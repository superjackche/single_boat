#include <stdio.h>
int main()
{
    int i = 0;
    for(i = 1; i <= 10; i++)//循环体内一般不要改变循环变量，否则容易造成死循环
    {
        printf("%d\n", i);
    }
    {
        if(i == 6)
        {
            //break;//跳出循环
            //continue;//跳过本次循环
        }
        printf("%d\n", i);
    }
    return 0;
}