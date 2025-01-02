#include <stdio.h>
int main (void)
{
    int *a,n;
    scanf("%d", &n);
    a = (int *)malloc(sizeof(int) * n);// 建立长度为n的动态整型数组
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        a[i] *= -10;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d", a[i]);
        if (i != n-1) printf(" ");
    }
    
    free(a);//释放动态内存。
}