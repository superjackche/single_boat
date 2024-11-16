#include <stdio.h>
#include <math.h>

// ����׳˵ĺ���
double factorial(int n) {
    double result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(){
    double x, single, sum = 1.0;
    int n = 1;

    scanf("%lf",&x);
    
    // ���� e^x
    do {
        single = pow(x, n) / factorial(n);
        sum += single;
        n++;
    } while (fabs(single) >= 1e-8);

    printf("%.4lf",sum);

    return 0;
}