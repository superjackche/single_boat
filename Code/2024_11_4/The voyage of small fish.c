#include <stdio.h>

int main() {
    int x = 0;
    long long n = 0, sum = 0;
    scanf("%d %lld", &x, &n);

    // ����������������ʣ�������
    long long complete_weeks = n / 7;
    long long remaining_days = n % 7;

    // ����������������Ӿ����
    sum += 250 * 5 * complete_weeks;

    // ����ʣ����������Ӿ����
    for (int i = 0; i < remaining_days; i++) {
        int current_day = (x + i - 1) % 7 + 1; // ���㵱ǰ���ܼ�
        if (current_day <= 5) { // ������
            sum += 250;
        }
    }

    printf("%lld", sum);
    return 0;
}