#include<stdio.h>
int main()
{
    int I,c,i,j;
    scanf("%d %d",&I,&c);
    for(i=1;i<=4*I+1;i++)
    {
    if(i%4==1)
    {
    for(j=1;j<=c;j++)
    printf("|*****");
    printf("|");
    }
    if(i%2==0)
    {
    for(j=1;j<=c;j++)
    printf("|  |  ");
    printf("|");
    }
    if(i%4==3)
    {
    for(j=1;j<=c;j++)
    printf("|--+--");
    printf("|");
    }
    printf("\n");
    }
    return 0;
}