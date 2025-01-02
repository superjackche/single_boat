#include <stdio.h>

void    printBasePower( int number , int base ) ;

int main()
{
    int        i , T , n , base ;
    
    scanf( "%d" , &T ) ;
    for ( i = 1 ; i <= T ; i++ )
    {
        scanf( "%d%d" ,  &n , &base ) ;
        printf("Test Cases %d :\n" , i ) ;
        printBasePower( n , base ) ;
    }
    
    return 0;
}

void    printBasePower( int number , int base )
{
    int a = 0, b = 1;
    while (number > 0)
    {
        a = number % base;
        number /= base;
        if (a != 0)
        {
            printf("%d %d\n", a, b);
        }
        b *= base;
    }
}