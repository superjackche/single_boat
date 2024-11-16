#include <stdio.h>

int findMax(int n) ;

int main()
{   
    int n ; 
    
    scanf("%d", &n); 
    printf("%d\n" , findMax( n ) ) ; 
    
    return 0;
}

int findMax(int n) {
    if (n == 1) {
        int number;
        scanf("%d", &number);
        return number;
    } else {
        int firstNumber;
        scanf("%d", &firstNumber);
        int maxOfRest = findMax(n - 1);
        return (firstNumber > maxOfRest) ? firstNumber : maxOfRest;
    }
}