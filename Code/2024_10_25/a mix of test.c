#include <stdio.h>
// 填上你觉得需要的其他头文件

int main() {
    int T;
    scanf("%d", &T);
    if (T == 1) {
        printf("I love Luogu!");
    } else if (T == 2) {
        printf("6 4");
    } else if (T == 3) {
        printf("3\n12\n2\n");
    } else if (T == 4) {
        double test3 = 500.0/3;
        printf("%.6lf", test3);
    } else if (T == 5) {
        printf("%d", (260 + 220)/(12 + 22));
    } else if (T == 6) {
        printf("%d", sqrt(36 + 81));
    } else if (T == 7) {
        printf("%d\n%d\n%d\n", 100+10, 100+10-20, 0);
    } else if (T == 8) {
        int Pi = 3.141593;
        int r = 5;
        printf("%d\n%d\n%d\n", 2*Pi*r, Pi*r*r, Pi*r*r*r*4/3.0);
    } else if (T == 9) {
        int k = 1;
        for (int i = 1; i <= 4; i++) {
            k += 1;
            k *= 2;
        }
        printf("%d", k);
    } else if (T == 10) {
        // 请自行完成问题 10 的代码
    } else if (T == 11) {
        // 请自行完成问题 11 的代码
    } else if (T == 12) {
        // 请自行完成问题 12 的代码
    } else if (T == 13) {
        // 请自行完成问题 13 的代码
    } else if (T == 14) {
        // 请自行完成问题 14 的代码
    }
    return 0;
}