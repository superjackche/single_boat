#include <stdio.h>

void swap(int *pa,int *pb)
{
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

int main()
{
    int a, b;
    printf("enter two numbers u want to exchange:");
    scanf("%d %d", &a, &b);
    swap(&a, &b);//记得带地址
    printf("the ending :\n%d %d", a, b);
    return 0;
}