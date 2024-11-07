#include<stdio.h>

int reverseNum(int) ; 

int main()
{
    int        num ;

    scanf("%d",&num);
    printf("The reverse form of number %d is %d.\n",num,reverseNum(num)) ;

    return 0;
}

int reverseNum(int n) {
    int answer = 0;
    int a = 0;
    while (n >= 1) {
        a = n % 10;
        answer = answer * 10 + a;
        n /= 10;
    }
    return answer;
}