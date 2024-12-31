#include <stdio.h>

// 定义一个结构体来返回两个值
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
    if (x % 2 == 0) result |= 1;      // 设置最低位表示偶数
    if (x > 4 && x <= 12) result |= 2; // 设置次低位表示在 5 到 12 之间
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
        case 0:  // 00 (0)：既不是偶数也不在 5 到 12 之间
            d++;
            break;
        case 1:  // 01 (1)：是偶数但不在 5 到 12 之间
        case 2:  // 10 (2)：不是偶数但在 5 到 12 之间
            b++;
            c++;
            break;
        case 3:  // 11 (3)：既是偶数也在 5 到 12 之间
            a++;
            b++;
            break;
    }
    */

    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}