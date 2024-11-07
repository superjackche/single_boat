#include<stdio.h>

int    fuc(int n) ;

int main()
{
    int n ;
    
    scanf("%d",&n); 
    printf("%d\n",fuc(n));
  
    return 0 ;
}

int    fuc(int n) {
    int sum = 0;
    if (n == 0) {
        sum = 0;
    } else {
        sum += n * n * n + fuc(n - 1);
    }
    return sum;
}