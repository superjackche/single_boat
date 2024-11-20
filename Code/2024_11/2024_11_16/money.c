#include <stdio.h>
int main() {
    int ch[100001] = {0};
    int num = 0;
    int sum = 0;
    scanf("%s", &ch);
    for (int i = 0; i< 100001; i++) {
        if (ch[i] >= '0' && ch[i] <='9') {
            num += ch[i];
        }
        if (ch[i+1] >= '0' && ch[i+1] <='9') {
            num += ch[i]*10;
        }
        if (ch[i+2] >= '0' && ch[i+2] <='9') {
            num += ch[i]*100;
        }
        if (ch[i+3] >= '0' && ch[i+3] <='9') {
            num += ch[i]*1000;
        }
        if (ch[i+4] >= '0' && ch[i+4] <='9') {
            num += ch[i]*10000;
        }
        sum += num;
    }
    printf("%d", sum);
    
}