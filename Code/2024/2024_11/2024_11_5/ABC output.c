#include <stdio.h>

int max3(int a, int b, int c){
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

int min3(int a, int b, int c){
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int main(){
    int a, b, c, max, mid, min;
    char ch[3] = {0};
    scanf("%d %d %d", &a, &b, &c);
    max = max3(a, b, c);
    min = min3(a, b, c);
    mid = a + b + c - max - min;
    scanf("%s", &ch);
    for (int i = 0; i < 3; i++) {
        if (ch[i] == 'A') printf("%d ", min);
        if (ch[i] == 'B') printf("%d ", mid);
        if (ch[i] == 'C') printf("%d ", max);
    }
    return 0;
}