/*现有若干行正整数，请你写一段程序分别统计每一行中有多少个质数。

输入格式:
第一行为一个整数n(0<n<=10)，代表测试用例行数。
后边是n行，每行为若干个用空格分隔的正整数。
这些正整数的最后是-1，表示此行结束。

输出格式:
为n行，每行一个整数，对应于输入的每一行中质数的个数。

测试用例保证输入合法，且所有整数可以用int存储*/
#include <stdio.h>
#include <stdbool.h>

// 判断一个数是否为质数的函数
int isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);  // 读取测试用例行数
    getchar();  // 读取换行符，避免影响后续输入

    for (int i = 0; i < n; i++) {
        int count = 0;  // 质数计数器
        int num;
        while (1) {
            scanf("%d", &num);  // 读取每个整数
            if (num == -1) {  // 如果读到-1，表示该行结束
                break;
            }
            if (isPrime(num)) {  // 如果是质数，则计数加1
                count++;
            }
        }
        getchar();  // 读取换行符，避免影响后续输入
        printf("%d\n", count);  // 输出该行的质数个数
    }

    return 0;
}