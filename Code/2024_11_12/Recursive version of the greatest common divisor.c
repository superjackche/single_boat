#include<stdio.h>

int GCD(int a , int b );

int main()
{
    int        a , b ;
    
    scanf("%d%d", &a , &b );
    printf( "%d\n" , GCD( a, b ) ) ;
     
    return 0 ;    
}

int GCD(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return GCD(b, a % b);
    }
}