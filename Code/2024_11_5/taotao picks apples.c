#include <stdio.h>

int main() {
    int apple_heights[10]; // �洢 10 ��ƻ���ĸ߶�
    int tao_tao_height;    // ���������ܹ��ﵽ�����߶�
    int num = 0;           // ��¼�����ܹ�ժ����ƻ����Ŀ

    // ��ȡ 10 ��ƻ���ĸ߶�
    for (int i = 0; i < 10; i++) {
        scanf("%d", &apple_heights[i]);
    }

    // ��ȡ���������ܹ��ﵽ�����߶�
    scanf("%d", &tao_tao_height);

    // ���������ܹ�ժ����ƻ����Ŀ
    for (int i = 0; i < 10; i++) {
        if (apple_heights[i] <= tao_tao_height + 30) { // ���ǰ�ʵĸ߶�
            num++;
        }
    }

    // ������
    printf("%d", num);

    return 0;
}