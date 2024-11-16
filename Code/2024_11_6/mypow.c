#include<stdio.h>

int mypow(int , int ) ;

int main()
{
    int x, n ;
    
    scanf("%d%d",&x,&n) ;
    printf("%d\n",mypow(x,n)) ;
                
    return 0;
}

int mypow(int x,int n) {
    int answer = 1;
    while (n--) {
        answer *= x;
    }
    return answer;
}