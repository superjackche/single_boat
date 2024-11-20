#include <stdio.h>

int getSum(int n , int a) ;

int main()
{
       int        n , a ; 
       
       scanf( "%d%d" , &n , &a );       
       printf( "%d\n" , getSum( n , a ) );

    return 0;
}

int getSum(int n , int a) {
    int sum = 0;
    if (n == 0) {
        sum = a;
    } else {
        sum += a + 3 * n + getSum(n - 1, a);
    }
    return sum;
}