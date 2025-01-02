#include <stdio.h>
int main(void)
{
    int n;
    int min = 11, max = 0;
    int nmax = 0, nmin = 0;
    int i, j, k;
    int sum = 0;
    int grades[1001] = {0};
    scanf("%d", &n);
    //读取并存储
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &grades[i]);
    }
    //遍历，找出最大值和其下标
    for (j = 0; j < n; j++)
    {
        if (grades[j] > max)
        {
            max = grades[j];
            nmax = j;
        }
    }
    
    //遍历，找出最小值和其下标
    for (k = 0; k < n; k++)
    {
        if (grades[k] < min)
        {
            min = grades[k];
            nmin = k;
        }
    }
    
    //赋0,清除最大值
    grades[nmax] = 0;
    //赋0,清除最小值
    grades[nmin] = 0;

    //求和
    for (int a = 0; a < n; a++)
    {
        sum += grades[a];
    }
    //输出平均分
    printf("%.2f", 1.0*sum/(n-2));
}