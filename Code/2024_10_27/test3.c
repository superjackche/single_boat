#include <stdio.h>
/*
int main(){
    char ch;
    int sum = 0;
    while ((ch = getchar()) != '\n') {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            putchar(ch);
        } else {
            sum++;
        }
    }
    printf("\n");
    printf("%d", sum);
    return 0;
}
*/
int main() {
    int ignoredCount = 0;
    char ch;

    // ��ȡ�����ַ�
    /*
    while (scanf("%c", &ch) = EOF && ch != '\n')Ϊʲô�����޷�����
    ���ȣ�������=��==������ӦΪ==
    ��Σ�ԭʼ�����е����� scanf("%c", &ch) == EOF && ch != '\n' �����߼����⡣
    scanf("%c", &ch) ����ֵΪ��ȡ�����ַ���������ȡ���ļ���������EOF��ʱ���� EOF�����򷵻� 1��
    ��ˣ�scanf("%c", &ch) == EOF �� ch != '\n' ����������������ͬʱΪ�棬��Ϊ�� scanf ���� EOF ʱ��ch ��ֵ��δ����ġ�
    */
    //while (scanf("%c", &ch) == 1 && ch != '\n') {
    while (ch != 'n') {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            printf("%c", ch);
        } else {
            ignoredCount++;
        }
    }
    /*while (scanf("%c", &ch) == 1) {
        if (ch == '\n') {
            break; // �������з�������ѭ��
        }
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            printf("%c", ch);
        } else {
            ignoredCount++;
        }
    }while (scanf("%c", &ch) == 1) {
        if (ch == '\n') {
            break; // �������з�������ѭ��
        }
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            printf("%c", ch);
        } else {
            ignoredCount++;
        }
    }*/

    // ������з�
    printf("\n");

    // ��������Ե��ַ�����
    printf("%d\n", ignoredCount);

    return 0;
}