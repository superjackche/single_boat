#include<stdio.h>

//插入排序（升序） 
//参数说明：数组，数组中已有元素个数 
void InsertSort(int a[],int n);

int main()
{
    int        n , i,    num[1000] ;
    
    scanf( "%d" , &n ); 
    for( i = 0 ; i < n ; i++ ) 
        scanf( "%d", &num[i] ) ;
    InsertSort( num , n ) ; 
    return 0 ;
}

void InsertSort(int a[], int n)
{
    for (int i = 1; i < n; i++) // 外层循环从索引1开始
    {
        int key = a[i];
        int j = i - 1;//j指向已排序序列的最后一个元素

        // 将大于 key 的元素向后移动一位
        while (j >= 0 && a[j] > key)//不断向前比较，直到找到不大于key的元素，或到达数组的起始位置
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;

        // 打印当前排序状态
        for (int k = 0; k < n - 1; k++)
        {
            printf("%d ", a[k]);
        }
        printf("%d\n", a[n - 1]);
    }
}