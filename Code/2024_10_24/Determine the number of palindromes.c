#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int n) {
    int reversed = 0;
    int original = n;
    
    // 反转数字
    while (n != 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    
    // 判断反转后的数字是否与原数字相同
    return original == reversed;
}

int main() {
    int num;
    
    scanf("%d", &num);
    
    if (isPalindrome(num)) {
        printf("Yes");
    } else {
        printf("No");
    }
    
    return 0;
}