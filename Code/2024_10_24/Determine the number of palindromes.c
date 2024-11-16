#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int n) {
    int reversed = 0;
    int original = n;
    
    // ��ת����
    while (n != 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    
    // �жϷ�ת��������Ƿ���ԭ������ͬ
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