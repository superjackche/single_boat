#include<stdio.h>
#include<stdlib.h>


int * create(int n) ;
void cal(int * array, int size) ;

int main()
{
    int * array , n , i ;
    
    scanf( "%d", &n );
    
    array = create(n) ;
    if ( array == NULL )
        return -1 ; //这里的return是因为没有获得内存而直接结束程序。
         
    cal( array, n) ;
    for ( i = 0 ; i < n ; i++ )
    {
        printf("%d" , *(array+i) ) ;
        if ( i == n - 1 ) printf("\n") ;
        else printf(" ") ;
    }     
    
    free(array) ;
    
    return 0;
}

int * create(int n)
{
    int *array = (int *)malloc(sizeof(int) * n);
    if (array == NULL)
    {
        return NULL;
    }
    return array;
}

void cal(int * array, int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }
    
    int max = 0;
    int min = 9999;
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += array[i];
        if (array[i] > max) max = array[i];
        if (array[i] < min) min = array[i];
    }
    printf("%d\n", sum);
    double average = sum*1.0/size;
    printf("%.2lf\n", average);
    printf("%d\n%d\n", max, min);
}