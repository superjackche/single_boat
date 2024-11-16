#include <stdio.h>

int    evaluation(int n,int a) ;
int main()
{
       int        n , a ; 
       
       scanf("%d%d",&n,&a);       
       printf("%d\n",evaluation(n,a));

    return 0;
}

int evaluation(int n,int a) {
    if (n == -1) {
        int s;
        return s + 1;
    } else {
        int s;
        s = pow(a,n + 1) + evaluation(n - 1, a);
        return s;
    }
}