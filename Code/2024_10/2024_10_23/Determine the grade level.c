/*���ٷ��Ƴɼ�score������ԭ�򻮷���ȼ���
score��90�ȼ�ΪA��
80 ��score<90���ȼ�ΪB��
70��score<80���ȼ�ΪC��
60��score<70,�ȼ�ΪD��
score<60,�ȼ�ΪE��

�����ʽ:
ֻ��һ������������ɼ�score������������֤��������������int�洢��
�����ʽ:
ֻ��һ�У����ɼ�С��0�����100ʱΪ"The score is out of range!"�����������ţ�
����Ϊ�����ѧ���ɼ���Ӧ�ĵȼ���*/

#include <stdio.h>
int main() {
    int score;
    scanf("%d",&score);
    if(score < 0 || score > 100) {
        printf("The score is out of range!");
    } else {
        switch(score / 10) {
            case 10: case 9: printf("A\n"); break;
            case 8: printf("B\n"); break;
            case 7: printf("C\n"); break;
            case 6: printf("D\n"); break;
            default :printf("E\n"); break;
        }
    }
    return 0;
}