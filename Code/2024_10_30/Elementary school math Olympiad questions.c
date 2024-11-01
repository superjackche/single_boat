#include <stdio.h>

//计算小数点后位数
int lens(int n) {
    int lens = 0;
    while (n <= 1) {
        n =  10;
        lens++;
    }
}

//计算每一项大小
double single(double n){
    double single = n/(n+2);
}
int main(){
    int n = 0;
    scanf("%d", &n);
    double sum = 0;
    for (double i = 1; i <= n; i += 2) {
        sum += single(i);
    }
    
    //turn sum into the simplest form of fraction
    
    return 0;
}