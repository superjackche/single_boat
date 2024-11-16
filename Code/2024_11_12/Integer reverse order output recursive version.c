#include <stdio.h>

void reverse(int n) ; 

int main()
{
    int     n;
         
    scanf("%d",&n);
    reverse(n) ;
    printf("\n");
    return 0;
}

void reverse(int n) {
    if (n >= 1) {
        printf("%d", n%10);
        reverse(n/10);
    }
}