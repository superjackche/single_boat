#include <stdio.h>
#include <string.h>

char ch1[27] = {'a','b','c',
                'd','e','f',
                'g','h','i',
                'j','k','l',
                'm','n','o',
                'p','q','r','s',
                't','u','v',
                'w','x','y','z',
                ' '};
char num1[27] = {'1','2','3',
                '1','2','3',
                '1','2','3',
                '1','2','3',
                '1','2','3',
                '1','2','3','4',
                '1','2','3',
                '1','2','3','4',
                '1'};

int how_much_num(char *ch, int n) {
    int num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 27; j++) {
            if (ch[i] == ch1[j]) {
                num += num1[j] - '0';
                break;
            }
        }
    }
    return num;
}

int main () {
    char ch[201] = {0};
    fgets(ch, sizeof(ch), stdin);
    int ans = how_much_num(ch, sizeof(ch));
    printf("%d", ans);
}