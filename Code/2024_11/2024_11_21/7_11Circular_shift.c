#include <stdio.h>
#include <stdlib.h>

void shift(int *array , int num , int size ) ;

int main()
{
    int        i , n , p , array[100] ;
    
    scanf(" %d%d" , &n , &p ) ;//测试用例保证0<p<n<=100
    for( i = 0 ; i < n ; i++ )
        scanf( "%d" , &array[i] ) ;//测试用例保证所有输入可以用整型存储

    shift( array , p , n ) ;//向左移p位
    for( i = 0 ; i < n - 1 ; i++ )
        printf( "%d " , array[i] ) ;
    printf( "%d\n" , array[i] ) ;
        
    return 0;    
}

//使用拼接的思维，将数组分为两部分，分别整体性的进行移位
void shift(int *array, int num, int size)
{
    if (size == 0) return; // 防止除以零

    num %= size; // 防止移位次数超过数组大小
    if (num == 0) return; // 无需移位

    int mid[100] = {0};

    // 1. 复制前 num 个元素到 mid 数组
    for (int j = 0; j < num; j++)
    {
        mid[j] = array[j];
    }

    // 2. 左移剩余的元素
    for (int i = num; i < size; i++)
    {
        array[i - num] = array[i];
    }

    // 3. 将 mid 数组中的元素复制到数组末尾
    for (int j = 0; j < num; j++)
    {
        array[size - num + j] = mid[j];
    }

}