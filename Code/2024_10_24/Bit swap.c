/*��֪һ��������n��������int�洢������������ǽ�n�����λ�����λ�ϵ����ֶԵ���
�ε�λ��θ�λ�ϵ����ֶԵ����Դ����ƣ�ֱ���м�λ��
���õ�һ�������������µ����������
��Ҫע����ǣ���������λ���������λ���ֶԵ������ֵĳ��ȱ��
��Ҳ�������λΪ0�������ܶ����������λ���Ե�����

�����ʽ:
ֻ��һ������������n��

�����ʽ:
��n���Խ������ֶԵ�ʱ������n=123����Ӧ�����321����
��n�����Խ����ֶԵ�ʱ������n=980����Ӧ�����The number cannot be changed.����

��������:
1365

�������:
5631*/
#include <stdio.h>
void print_digits_recursively(int n) {
    if (n < 10) {
        if (n == 0) {
            printf("The number cannot be changed.");
        } else {
            printf("%d", n);
        }
    } else {
        printf("%d", n % 10);
        print_digits_recursively(n / 10);
    }
}
int main(){
    int n;
    scanf("%d", &n);
    print_digits_recursively(n);
    return 0;
}