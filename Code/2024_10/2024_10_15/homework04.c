#include<stdio.h>
int main()
{
    int n,a,sum=0;
    int temp=0,max=-1000000,min=1000000;
    scanf("%d",&n);
    while(temp<n)
    {
        scanf("%d",&a);
        temp++;
        sum+=a;
        if(a>max)
        max=a;
        if(a<min)
        min=a;
    }
    printf("%d %d %d",sum,max,min);
    return 0;
}