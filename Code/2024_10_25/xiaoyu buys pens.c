#include <stdio.h>
#include <math.h>
int main(){
    int a, b, num;
    scanf("%d %d", &a, &b);
    num = floor((a*10 + b)/19);
    printf("%d", num);
    return 0;
}
/*floor()���� ����ȡ��
  ceil()���� ����ȡ��
  round()���� ��������ȡ��*/