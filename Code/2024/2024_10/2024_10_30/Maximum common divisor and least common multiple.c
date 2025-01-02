#include <stdio.h>

// ��������������Сֵ
int Min(int m, int n) {
    return m > n ? n : m;
}

// ʹ��ŷ������㷨�������Լ��
int Maximun_common_divisor(int m, int n) {
    while (n != 0) {
        int temp = n;
        n = m % n;
        m = temp;
    }
    return m;
}

int main() {
    int m, n, gcd, lcm;
    scanf("%d%d", &m, &n);

    // �������Լ��
    gcd = Maximun_common_divisor(m, n);

    // ������С�������������������
    lcm = (m / gcd) * n;

    // ������
    printf("%d %d\n", gcd, lcm);

    return 0;
}