#include <stdio.h>

// �ݹ麯�������ڴ�ӡ���ֵ�ÿһλ
void print_digits_recursively(int n) {
    if (n < 10) {
        // ��� n ��һλ����ֱ�����
        printf("%d", n);
    } else {
        // �ȵݹ鴦���λ����
        print_digits_recursively(n / 10);
        // �������ǰλ����
        printf(" %d", n % 10);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // ���õݹ麯������������
    print_digits_recursively(n);
    printf("\n");

    return 0;
}