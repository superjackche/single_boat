#include <stdio.h>
int main(){
    int n;
    int num;
    int min = 1000;
    int max = 0;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &num);
        if (num > max) max = num;
        if (num < min) min = num;
    }
    printf("%d", max - min);
    return 0;
}