#include <stdio.h>

// ����һ���ṹ������������ֵ
typedef struct {
    int even;
    int range;
} MatchResult;

MatchResult match_num(int x) {
    MatchResult result = {0, 0};
    if (x % 2 == 0) result.even = 1;
    if (x > 4 && x <= 12) result.range = 1;
    return result;
}

/*int match_num(int x) {
    int result = 0;
    if (x % 2 == 0) result |= 1;      // �������λ��ʾż��
    if (x > 4 && x <= 12) result |= 2; // ���ôε�λ��ʾ�� 5 �� 12 ֮��
    return result;
}
*/

int main() {
    int x = 0;
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d", &x);

    MatchResult result = match_num(x);

    if (result.even == 0 && result.range == 0) {
        d++;
    } else if ((result.even == 0 && result.range == 1) || (result.even == 1 && result.range == 0)) {
        b++;
        c++;
    } else if (result.even == 1 && result.range == 1) {
        a++;
        b++;
    }

    /*
    int result = match_num(x);

    switch (result) {
        case 0:  // 00 (0)���Ȳ���ż��Ҳ���� 5 �� 12 ֮��
            d++;
            break;
        case 1:  // 01 (1)����ż�������� 5 �� 12 ֮��
        case 2:  // 10 (2)������ż������ 5 �� 12 ֮��
            b++;
            c++;
            break;
        case 3:  // 11 (3)������ż��Ҳ�� 5 �� 12 ֮��
            a++;
            b++;
            break;
    }
    */

    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}