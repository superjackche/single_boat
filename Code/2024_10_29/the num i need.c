#include <stdio.h>

int Sum_of_squares_of_various_numbers(int n) {
    int sum = 0;
    while(n >= 1) {
        int k = n % 10;  
        sum = k*k + sum;
        n = n / 10;
    }
    return sum;
}

int main(){
    int n = 0, m = 0;
    scanf("%d %d",&n, &m);
    for (int i = 1; i <= n; i++) {
        int a = i / m;
        if (a == Sum_of_squares_of_various_numbers(i)) {
            printf("%d\n", i);
        }
    }
    return 0;
} 