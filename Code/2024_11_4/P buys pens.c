#include <stdio.h>
#include <math.h>

int main(){
    int n;
    int sum0 = 100000000;
    int pen, prize;

    scanf("%d", &n);

    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &pen, &prize);
        int sum = ceil(1.0 * n / pen)*prize;//ceil向上取整，注意运算*1.0
        if (sum < sum0) {
            sum0 = sum;
        }
    }

    printf("%d", sum0);
    return 0;
}