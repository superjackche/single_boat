#include <stdio.h>
int main()
{
    int a = 10;
    int arr[10] = { 0 };
    int num = sizeof(arr) / sizeof(0);//计算数组中元素的个数
    printf("%d\n", sizeof(a));  //sizeof是一个操作符，用来获取类型或变量占用的内存字节数，不是函数
    printf("%d\n", sizeof(int));    //此处括号不能省略
    printf("%d\n", sizeof a);
    printf("%d\n", sizeof(arr));    //计算的是数组的总长度，而不是数组中元素的个数，单位是字节
    printf("%d\n",num);
    return 0;
}