#include<stdio.h>

#define        MAX        100

int    getBigNumbers( int numbers[] , int bigNumbers[] , int size) ;

int main()
{
    int        i , m , n ,    numbers[MAX] , bigNumbers[MAX];
    
    scanf( "%d" , &n ) ;
    for ( i = 0 ; i < n ; i++ )
        scanf( "%d" ,  &numbers[i] ) ;
    
    m = getBigNumbers( numbers , bigNumbers , n ) ;
    for ( i = 0 ; i < m ; i++ )
    {
        if ( i == m - 1 )
            printf( "%d\n" ,  bigNumbers[i] ) ;
        else
            printf( "%d " ,  bigNumbers[i] ) ;
    }
    
    return 0;
}

int    getBigNumbers( int numbers[] , int bigNumbers[] , int size) {
    double ave = 0;
    int m = 0;
    for (int i = 0; i < size; i++) {
        ave += numbers[i];
    }
    ave /= size*1.0;
    for (int i = 0; i < size; i++) {
        if (numbers[i] > ave) {
            bigNumbers[m++] = numbers[i];
        }
    }
    return m;
}