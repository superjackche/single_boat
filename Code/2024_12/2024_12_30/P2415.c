#include <stdio.h>
#include <math.h>

int main() {
    int num;
    int count = 0;
    long long sum = 0;
    
    // 读取输入的每个数字，并统计个数
    while (scanf("%d", &num) == 1) {
        sum += num;
        count++;
    }
    
    //2^(count-1)
    if (count > 0) {
        long long factor = (long long)pow(2.0, count - 1.0);
        sum *= factor;
    }
    
    printf("%lld\n", sum);
    return 0;
}