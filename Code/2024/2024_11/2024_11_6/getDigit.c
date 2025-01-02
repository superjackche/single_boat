#include<stdio.h>

int getDigit(long long n); 

int main()
{
    long long     n ;
    int            len ;
    
    scanf("%lld",&n);
    len = getDigit(n) ;
    if (len > 1)
        printf("The integer %lld has %d digits.\n",n, len) ;
    else
        printf("The integer %lld has %d digit.\n",n, 1) ;
    return 0 ;    
}

int getDigit(long long n) {
    int len = 0;
    while (n >= 1) {
        len++;
        n /= 10;
    }
    return len;
}