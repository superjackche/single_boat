#include <stdio.h>
int main()
{
    int i = 1;
    while (i <=10)//如果想增加后续的连续使用性，可以将10用字符替换，如“Max”，前面定义“Max”即可
    {
        /*if (i == 5)
            break;*///在while循环中，break用于永久跳出循环，continue用于结束本次循环（即不执行其之后的此次循环范围内的代码），继续执行下一次循环（可能陷入死循环）

        printf("%d\n", i);
        i++;
    }

    return 0;
}