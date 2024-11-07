#include <stdio.h>

//�ж�һ�����Ƿ�Ϊ��ȫ���ĺ���
int        isPerfect(int);

//��ӡ��ȫ���ĺ��� 
void    printPerfect(int);

int main()
{
    int i,a,b,count;
    
    scanf("%d%d",&a,&b);
    count = 0 ;//a,b��������ȫ������������ʼ��Ϊ0 
    for(i=a;i<=b;i++)
    {
        if (isPerfect(i))  //�������ȫ�� 
        {
            printPerfect(i) ;//��ӡ����ȫ�� 
            count ++ ;  //��������1 
        }        
    }
    printf("The total number is %d.\n",count);//���a,b��������ȫ�������� 
    return 0 ;
}

int isPerfect(int n) {
    if (n == 1) return 0;
    int sum = 1;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    if (sum == n) {
        return 1;
    } else {
        return 0;
    }
}

void printPerfect(int n) {
    printf("%d=1", n);
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            printf("+%d", i);
        }
    }
    printf("\n");
}