#include <stdio.h>
#include <math.h>
int main(){
    int a, b, c, sum;
    scanf("%d %d %d", &a, &b, &c);
    sum = round(a*0.2 + b*0.3 + c*0.5);
    printf("%d", sum);
    return 0;
}