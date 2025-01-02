#include <stdio.h>
#include<stdio.h>

//将只包含小写字母的字符串str中的元音字母复制到字符数组vowel,并返回元音字符的个数。
int getVowel(char str[],char vowel[]);
 
int main()
{
    char    vowel[101] , str[101];//每个数组都至少要101个字节 
    int        len ;
    
    scanf("%s",str);    //读入字符串 
    len = getVowel(str,vowel);    //复制 
    if ( len > 0 ) printf("%d %s\n", len , vowel);    //输出复制后结果 
    else printf("%d\n", len);//仅输出长度 
    
    return 0;    
}

int getVowel(char str[],char vowel[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        return 0;
    }
    int j = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        switch (str[i])
        {
        case 'a':
            vowel[j] = 'a';
            j++;
            break;
        case 'e':
            vowel[j] = 'e';
            j++;
            break;
        case 'i':
            vowel[j] = 'i';
            j++;
            break;
        case 'o':
            vowel[j] = 'o';
            j++;
            break;
        case 'u':
            vowel[j] = 'u';
            j++;
            break;

        default:
            break;
        }
    }
    vowel[j] = '\0';  // 添加字符串结束符
    //字符串结束符很重要：在处理字符串时，别忘了在适当的位置添加 '\0'，否则可能会导致输出异常或程序崩溃。
    return j;
}