#include<stdio.h>

void printFactor( int, int ); 

int main()
{
    int a,b,i ;
    
    scanf( "%d%d", &a, &b );
    for( i = a ; i <= b ; i++ )
        printFactor( i , 1 ) ;    
    
    return 0;
}

int isPrime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n%i == 0) {
            return 0;
        }
    } return 1;
}

void printFactor(int n, int factor) {
    if (n == 1) {
        printf("1=1\n");
        return;
    }

    if (factor == 1) {
        printf("%d=", n);
        factor = 2;
    }

    if (n % factor == 0) {
        printf("%d", factor);
        n /= factor;
        if (n != 1) {
            printf("*");
        } else {
            printf("\n");
            return;
        }
        printFactor(n, factor);
    } else {
        if (factor == 2) {
            printFactor(n, factor + 1);
        } else {
            printFactor(n, factor + 2);
        }
    }
}