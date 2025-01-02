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

void    printBasePower( int number , int base ) {
    int n = 0;
    int lens = 0;
    int number0 = number;
    while (number0 > 0) {
        number0 /= 10;
        lens++;
    }
    for (int i = 0; ; i++) {
        if (number % base != 0) {
            printf("%d %d\n" ,number / base, pow(base, n));
        }

        n++;
        number /= base;
        base *= base;
    }
}
