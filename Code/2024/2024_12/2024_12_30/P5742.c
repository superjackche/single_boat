#include <stdio.h>

typedef struct {
    char id[7];
    int score1;
    int score2;
    int sum;
    int sign;
} Stu;

int main() {
    int n = 0;
    scanf("%d", &n);
    Stu stu[n];


    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", stu[i].id, &stu[i].score1, &stu[i].score2);
        stu[i].sum = stu[i].score1 * 7 + stu[i].score2 * 3;
        stu[i].sign = 0;    //初始化为0
    }

    //判断加权综合成绩是否符合要求
    for (int i = 0; i < n; i++) {
        if ((stu[i].score1 + stu[i].score2) > 140 &&
            stu[i].sum >= 800) {
                stu[i].sign = 1;
        }
    }

    //输出
    for (int i = 0; i < n; i++) {
        if (stu[i].sign == 1) {
            printf("Excellent\n");
        } else {
            printf("Not excellent\n");
        }
    }

    return 0;
}