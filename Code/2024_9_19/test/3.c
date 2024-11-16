#include <stdlib.h>
#include <stdio.h>
#define M 100 //定义最多处理的字符数

void RLE(char target[])
{
    int Chcount = 0;  //字符计数器置为0
    int Repcount = 0; //将重复计数器置为0
    char temp;
    char ch;
    for (int i = 0; target[i] != '\0'; i++)
    {
        ch = target[i];
        Chcount++;
        if (Repcount == 0)
        {
            Repcount++;
            temp = ch;
        }
        else
        {
            if (temp == ch)
            {
                Repcount++;
            }
            else if (Repcount >= 4) //重复四次或者多余四次时进行RLE编码
            {
                Chcount = Chcount - Repcount - 1; //更新插入字符的位置
                target[Chcount] = '*';
                target[Chcount + 1] = Repcount + '0';
                target[Chcount + 2] = temp;
                Chcount += 3;
                target[Chcount] = ch;
                Chcount++;
                Repcount = 1;
                temp = ch;
            }
            else
            {
                temp = ch;
                Repcount = 1;
            }
        }
    }
    if (Repcount >= 4) //重复四次或者多余四次时进行RLE编码
    {
        Chcount = Chcount - Repcount ; //更新插入字符的位置
        target[Chcount] = '*';
        target[Chcount + 1] = Repcount + '0';
        target[Chcount + 2] = temp;
        Chcount += 3;
    }
    target[Chcount] = '\0';
}

int main()
{
    char original[M];
    scanf("%s", original);
    RLE(original);
    for (int i = 0; original[i] != '\0'; i++)
        printf("%c", original[i]);
    system("pause");
    return 0;
}