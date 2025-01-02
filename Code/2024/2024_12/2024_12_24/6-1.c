#include <stdio.h>

#define        MAX        100

void    changeArray(int * array , int size ) ;

int main()
{
    int        array[MAX] ;
    int        n , i ;
    
    scanf( "%d" , &n );

    for( i = 0 ; i < n ; i++) 
    {
        scanf( "%d" , &array[i] ); 
    }
    
    changeArray(array , n ) ;
    
    for( i = 0 ; i < n - 1 ; i++) 
    {
        printf( "%d " , array[i] ); 
    }   
    printf( "%d\n" , array[i] ); 
    
    return 0;
}

void    changeArray(int * array , int size ) {
    int a1[MAX] = {0};
    int a2[MAX] = {0};
    int len1 = 0;
    int len2 = 0;
    for (int i = 0, j = 0, k = 0; i < size; i++) {
        if (array[i]%2 == 0) {
            a1[j++] = array[i];
            len1++;
        } else if (array[i]%2 == 1) {
            a2[k++] = array[i];
            len2++;
        }
    }
    for (int i = 0; i < len1; i++) {
        array[i] = a1[i];
    }
    for (int i = len1; i < len1+len2; i++) {
        array[i] = a2[i-len1];
    }
}