#include<stdio.h>

int getString( char * source , char *strPtr[] ) ;

int main()
{
    char    str[100005];
    char    *strPtr[1005]={0};
    int        i, num ;
    
    gets(str);
    num = getString( str , strPtr ) ;
    for( i = 0 ; i < num ; i++ )
        puts(strPtr[i]);
    
    return 0;    
}

int getString(char *source, char **strPtr)
{
    int i = 0, j = 0;

    // 跳过字符串开头的空格
    while (source[i] == ' ')
    {
        i++;
    }

    // 记录第一个非空格字符的地址
    strPtr[j++] = &source[i];

    while (source[i] != '\0')
    {
        if (source[i] == ' ')
        {
            source[i] = '\0'; // 将空格替换为字符串结束符

            // 跳过中间的连续空格
            while (source[++i] == ' ')
            {
                if (source[i] == '\0')
                {
                    return j;
                }
            }

            // 确保未到字符串结尾，再记录下一个单词的起始地址
            if (source[i] != '\0')
            {
                strPtr[j++] = &source[i];
            }
        }
        else
        {
            i++;
        }
    }
    return j;
}