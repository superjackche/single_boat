#include<stdio.h>

//函数功能：二分查找
//函数参数：分别为被查找的数组，数组长度，所查找的元素
//函数返回值：如果找到，则返回该元素在数组中的下标，否则返回-1 
int BinarySearch(int a[],int n,int key) ; 

int main()
{
    int    num[200] ; 
    //这个数组比较大，如果在你的电脑中无法分配这么大的内存，请改小后测试。
    int        n , m, i;    
    int        key ;
    
    scanf("%d%d",&n,&m); 
    for( i = 0 ; i < n ; i++ ) 
        scanf("%d",&num[i]) ;
        
    for( i = 0 ; i < m ; i++ ) 
    {
        scanf("%d",&key) ;
        printf("%d",BinarySearch(num,n,key)) ;
        if ( i != m - 1 ) printf(" ") ;
        else printf("\n") ;
    }
    return 0 ;
}


int BinarySearch(int a[],int n,int key)
{
    if (key < a[0] || key > a[n-1]) return -1;
    int p = 0, q = n-1, mid = (p+q)/2;
    for (int i = mid; mid <= q; i++)
    {
        if (a[i] > key)
        {
            q = mid;
            mid = (p+q)/2;
        }
        else if (a[i] < key)
        {
            p = mid;
            mid = (p+q)/2;
        }
        else return i;
    }
    return -1;
}