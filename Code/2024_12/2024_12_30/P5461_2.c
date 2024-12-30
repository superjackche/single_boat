#include <stdio.h>
#include <math.h>

// 计算赦免状态的函数
int determine_forgiveness(int i, int j, int n) {
    for(int k = n - 1; k >= 0; k--) {
        // 检查第k位是否在左上角
        if( ((i >> k) & 1) == 0 && ((j >> k) & 1) == 0 ) {
            return 0; // 被赦免
        }
    }
    return 1; // 未被赦免
}

int main(){
    int n;
    scanf("%d", &n);
    int size = 1 << n; // 计算2^n

    // 遍历每个位置并确定其赦免状态
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int status = determine_forgiveness(i, j, n);
            printf("%d", status);
            if(j != size - 1){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}