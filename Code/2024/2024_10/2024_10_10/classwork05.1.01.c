/*��֪һ������n����Ҫ����n��ӡ��n�׵�ʵ�����Ρ�

�����ʽ:
ֻ��һ������n(0<n<40������Ҫ��ӡ�����ν���)������������֤�Ϸ���

�����ʽ:
n��ʵ������(ռ2��n-1��)��*/
#include <stdio.h>

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
        // ��ӡ�ո�
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }
        // ��ӡ�Ǻ�
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }
        printf("\n");
    }

    // ��ӡ�°벿��
    for (int i = n - 1; i >= 1; i--) {
        // ��ӡ�ո�
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }
        // ��ӡ�Ǻ�
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}