#include <stdio.h>
int main()
{
    int a = 10;
    if (5 == a)//关键点在这里，将5前置，避免对a重新赋值而导致if语句在非正确前提下执行
    {
        printf("hehe/n");
    }
    else
    {
        printf("haha/n");
    }
}