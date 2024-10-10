/*��֪һ������n����Ҫ����n��ӡ��n�׵�ʵ�����Ρ�

�����ʽ:
ֻ��һ������n(0<n<40������Ҫ��ӡ�����ν���)������������֤�Ϸ���

�����ʽ:
n��ʵ������(ռ2��n-1��)��*/
#include <stdio.h>

void printSpaces(int count) {
    for (int j = 1; j <= count; j++) {
        printf(" ");
    }
}

void printStars(int count) {
    for (int k = 1; k <= count; k++) {
        printf("*");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    // ��֤����
    if (n < 1 || n > 39) {
        printf("Error: Invalid input (0 < n < 40)\n");
        return 1;
    }

    // ��ӡ�ϰ벿��
    for (int i = 1; i <= n; i++) {
        printSpaces(n - i);
        printStars(2 * i - 1);
        printf("\n");
    }

    // ��ӡ�°벿��
    for (int i = n - 1; i >= 1; i--) {
        printSpaces(n - i);
        printStars(2 * i - 1);
        printf("\n");
    }

    return 0;
}