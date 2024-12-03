#include<stdio.h>

#define        MAXLEN        110

int        isPrime( int n ) ;//判断一个整数是否是质数，是则返回1，否则返回0 
int        getResult( char word[] ) ;

int main()
{
    char    word[MAXLEN] ;

    scanf( "%s" , word ) ;            
    printf( "%d\n" , getResult( word ) );

    return 0;
}

int        getResult( char word[] )
{
    int ch[256] = {0};
    int min = 9999;
    int max = 1;
    int ans = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        ch[word[i]]++;
    }

    for (int j = 1; j < 256; j++)
    {
        if (ch[j] > max) max = ch[j];
        if (ch[j] != 0 && ch[j] < min) min = ch[j];
    }

    ans = max - min;
    if (isPrime(ans) != 1) ans = -1;
    
    return ans;
}