/*��֪������n�����й�ʽ:

An = 1*2*3+2*3*4+3*4*5+��+(n-2)*(n-1)*n (n>=3)

An = 0 (n=1,2)

�����nֵ��������е�ǰn��͵�ֵ,�������n��ȡֵ��Χ��(1<=n<=3000)��

ע�⣺�����An ֻ��һ�������Ҫ����Ǽ�������е�ǰn��͡�

��ʾ������nֵ�ܴ󣬽���ʹ��long long�ͱ����洢�����*/
#include <stdio.h>

long long An(int n){
    if (n == 1 || n == 2) return 0;
    long long sum = 0;
    for(int i = 3;i <= n;i++){
        sum += (long long)(i - 2) * (i - 1) * i;
    }
    return sum;
}

long long sum0(int n){
    if (n <+3) return 0;
    long long sum1 = 0;
    for (int i = 1; i <= n; i++) sum1 += An(i);
    return sum1;
}
int main(){
    int n;
    scanf("%d", &n);
    printf("%lld\n", sum0(n));
    return 0;
}