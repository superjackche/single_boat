/*����һ���ַ����ֱ�ͳ�Ƴ�����Ӣ����ĸ���ո����ֺ������ַ��ĸ�����

�����ʽ:
ֻ��һ�У�Ϊһ���ַ����У��ַ����г���С��100���Իس���������

�����ʽ:
ֻ��һ�У�Ϊ4���ÿո�ָ������������δ��������ַ�������Ӣ���ַ����ո������Լ������ַ���������*/
#include <stdio.h>
#include <ctype.h> // �����ַ�������

int main() {
    char input[101]; // �����ַ����г���С��100����һ������λ�ø��ַ���������'\0'
    int letters = 0, spaces = 0, digits = 0, others = 0;

    // ��ȡһ���ַ�
    fgets(input, 101, stdin);

    // �����ַ����в�ͳ��
    for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
        if (isalpha(input[i])) { // �����Ӣ����ĸ
            letters++;
        } else if (isspace(input[i])) { // ����ǿո�
            spaces++;
        } else if (isdigit(input[i])) { // ���������
            digits++;
        } else { // �����ַ�
            others++;
        }
    }

    // ������
    printf("%d %d %d %d\n", letters, spaces, digits, others);

    return 0;
}