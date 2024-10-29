#include <stdio.h>
#include <math.h>
int main(){
    int m, t, s;
    scanf("%d%d%d", &m, &t, &s);
    if (t != 0) {
        double k = (s*1.0) / (t*1.0);
        int remain = m - ceil(k);
        if (remain > 0) {
            printf("%d", remain);
        } else {
            printf("0");
        }
    } else {
        printf("0");
    }
    return 0;
}