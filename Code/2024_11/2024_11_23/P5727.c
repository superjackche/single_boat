#include <stdio.h>
int main(void)
{
    int ch[1024] = {0};
    int num;
    int time = 0;
    scanf("%d", &num);
    while (num != 1)
    {
        ch[time] = num;
        if (num % 2 == 1)
        {
            num = num*3 + 1;
        }
        else
        {
            num /= 2;
        }
        time++;
    }
    ch[time] = 1;
    for (int j = time; j >= 0; j--)
    {
        printf("%d ", ch[j]);
    }

}