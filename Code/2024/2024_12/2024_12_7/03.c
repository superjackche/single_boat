#include <stdio.h>

void    output( int n ) ;

int main()
{
    int        n ;
    
    scanf( "%d" , &n ) ;
    output( n ) ;
    
    return 0 ;
}

void print(int n, int j)   //没想到吧，这个也要用递归
{
    if (n == 1)
    {
        printf("%d\n", j);
    }
    else
    {
        printf("%d ", j);
        print(n-1, j);
    }
}

void    output( int n )
{
    if (n != 1)
    {
        output(n-1);
        print(n, n);
    }
    else
    {
        print(n, n);
        return n+1;
    }
}