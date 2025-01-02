#include<stdio.h>

void bubbleSort(int a[],int n);
void func1(int a[]);
void func2(int *a);

//输出数组中所有元素 
void outputData(int data[],int elementCount) ;

int main()
{
    int        n , i,    num[10010] ;
    
    scanf("%d",&n); 
    for( i = 0 ; i < n ; i++ ) 
        scanf("%d",&num[i]) ;
    bubbleSort(num,n) ; 
    outputData(num,n) ;
    return 0 ;
}



void bubbleSort(int a[],int n)
{
    for (int j = n-1; j > 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if (a[i] > a[i+1])
            {
                int temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
            }
        }
    }
}

void func1(int a[]) {
    // 操作数组
}

void func2(int *a) {
    // 操作数组
}

void outputData(int data[],int elementCount)
{
    for (int i = 0; i < elementCount-1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("%d\n", data[elementCount-1]);
}