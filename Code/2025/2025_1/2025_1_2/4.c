#include <stdio.h>
#include <string.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        char num[1000000] = { '\0' };
        scanf("%s", num);

        long long sum = 0;
        long long n = strlen(num);

        // 先得到所有位的总和
        for (int j = 0; j < n; j++) {
            sum += (num[j] - '0');
        }

        // 不断将 sum 的各位相加，直到 sum 小于 10
        while (sum >= 10) {
            long long temp = 0;
            while (sum > 0) {
                temp += sum % 10;
                sum /= 10;
            }
            sum = temp;
        }

        printf("%lld\n", sum);
    }
    return 0;
}