#include <stdio.h>
#include <ctype.h>

int main() {
    int t;
    char str[32]; // �ַ������Ȳ�����30����1���ڴ洢������

    // ��ȡ������������
    scanf("%d", &t);
    getchar(); // ���ջ��з�

    while (t--) {
        fgets(str, sizeof(str), stdin); // ��ȡһ���ַ���
        int len = 0;
        
        while (str[len] != '\n' && str[len] != '\0') {
            len++;
        }
        str[len] = '\0'; // ȥ�����з�

        // ����ַ����Ƿ�Ϊ��
        if (len == 0) {
            printf("no\n");
            continue;
        }

        // ���ǰ��0
        if (str[0] == '0' && len > 1) {
            printf("no\n");
            continue;
        }

        // ���������
        int i = 0;
        if (str[0] == '+' || str[0] == '-') {
            i++;
            if (i >= len || str[i] == '0') {
                printf("no\n");
                continue;
            }
        }

        // ���ʣ���ַ�
        for (; i < len; i++) {
            if (!isdigit(str[i])) {
                printf("no\n");
                break;
            }
        }

        if (i == len) {
            printf("yes\n");
        }
    }

    return 0;
}