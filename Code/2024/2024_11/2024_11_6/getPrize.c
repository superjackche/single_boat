#include<stdio.h>

double getPrize(double x);

int main()
{
    double    x ;
    
    scanf("%lf",&x);
    printf("The prize is %.4f.\n",getPrize(x)) ;

    return 0 ;    
}

double getPrize(double x) {
    double sum = 0;
    if (x <= 10) {
        sum = x * 0.1;
    } else if (x > 10 && x <= 20) {
        sum = 10 * 0.1 + (x - 10) * 0.075;
    } else if (x > 20 && x <= 40) {
        sum = 10 * 0.1 + 10 * 0.075 + (x - 20) * 0.05;
    } else if (x > 40 && x <= 60) {
        sum = 10 * 0.1 + 10 * 0.075 + 20 * 0.05 + (x - 40) * 0.03;
    } else if (x > 60 && x <= 100) {
        sum = 10 * 0.1 + 10 * 0.075 + 20 * 0.05 + 20 * 0.03 + (x - 60) * 0.015;
    } else if (x > 100) {
        sum = 10 * 0.1 + 10 * 0.075 + 20 * 0.05 + 20 * 0.03 + 40 * 0.015 + (x - 100) * 0.01;
    }
    return sum;
}