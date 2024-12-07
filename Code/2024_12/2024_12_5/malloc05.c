#include <stdio.h>
int main (void)
{
    int **a,n ,m;
    scanf("%d%d",&n,&m);
    a=(int **)malloc(sizeof(int *)*n);//建立长度为n的动态指针数组
    for(int i=0;i<n;i++)
    a[i]=(int *)malloc(sizeof(int)*m);//建立长度为m的一维整型数组

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a[i][j] *= -10;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d", a[i][j]);
            if (j != m-1) printf(" ");
        }
        printf("\n");
    }


    for(int i=0;i<n;i++)
    free(a[i]);
    free(a);//释放动态内存。
}