#include<stdio.h>

#define        MAXLEN        100

int    put(int set[] , int length , int element);

int main()
{
    int        i , num , set[MAXLEN];
    int        len = 0 ;

    scanf( "%d" , &num ) ;
    while ( num != -1 ){
        len = put(set , len , num);
        scanf( "%d" , &num ) ;
    }
    for (i = 0 ; i < len - 1 ; i++)
        printf( "%d " , set[i] ) ;
    printf( "%d\n" , set[i] ) ;
    
    return 0;
}

int    put(int set[] , int length , int element)
{
    int sign = 0;
    if (length == 0)
    {
        set[0] = element;
        return 1;
    }
    for (int i = 0; i <= length; i++)
    {
        if (set[i] == element) sign = 1;
    }
    if (sign == 0)
    {
        set[length] = element;
        return length+1;
    }
    else
    {
        return length;
    }
}