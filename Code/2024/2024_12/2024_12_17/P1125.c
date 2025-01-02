#include <stdio.h>
#include <string.h>
int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main (void) {
    char raw[101] = {0};
    int num[27] = {0};
    int min = 101, max = 0;
    scanf("%s", raw);
    int len = strlen(raw);
    for (int i = 0; i < len; i++) {
        num[raw[i]-'a']++;
    }
    for (int j = 0; j < 26; j++) {
        if (num[j] == 0) continue;
        if (num[j] > max) max = num[j];
        if (num[j] < min) min = num[j];
    }
    int temp = max - min;
    if (is_prime(temp)) {
        printf("Lucky Word\n");
        printf("%d", temp);
    } else {
        printf("No Answer\n0");
    }
}