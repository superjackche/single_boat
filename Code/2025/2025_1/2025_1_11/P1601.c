#include <stdio.h>
#include <string.h>
#define MAX 1001

int main() {
    char num1[MAX] = {0};
    char num2[MAX] = {0};
    char ans[MAX + 1] = {0};  // 多一位存储可能的进位
    
    scanf("%s%s", num1, num2);
    
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxlen = len1 > len2 ? len1 : len2;
    
    // 右对齐数字
    for(int i = len1 - 1, j = maxlen - 1; i >= 0; i--, j--) {
        ans[j] = num1[i];
    }
    for(int i = len1 - 1; i >= 0; i--) {
        if(ans[i] == 0) ans[i] = '0';
    }
    
    // 处理加法
    int carry = 0;
    for(int i = maxlen - 1; i >= 0; i--) {
        int sum = (ans[i] - '0') + (num2[len2 - 1 - (maxlen - 1 - i)] - '0') + carry;
        ans[i] = sum % 10 + '0';
        carry = sum / 10;
    }
    
    // 处理最高位进位
    if(carry) {
        printf("1");
    }
    
    //没想到吧哥们，要输出的是数字0-9，不能是ASCII格式的48-57
    int final_len = strlen(ans);
    for (int i = 0; i < final_len; i++) {
        if (ans[i] >= '0' && ans[i] <= '9') {
            int num = ans[i] - '0';
            printf("%d", num);
        }
    }
    
    return 0;
}