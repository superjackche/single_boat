#include <stdio.h>

int main(){
    int a = 0, b = 0, sum = 0, answer = 0;
    for (int i = 1; i <= 7; i++) {
        scanf("%d %d", &a, &b);
        if ((a + b) > sum && (a + b) > 8) {
            sum = a + b;
            answer = i;
        }
    }
    printf ("%d", answer);
    return 0; 
}