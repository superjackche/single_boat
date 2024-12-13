#include <stdio.h>
#define MAX 22

struct stu {
    char name[MAX];
    char id[MAX];
    int score[6];
} ;

void sort(int *num) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (num[j] < num[j+1]) {
                int temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    struct stu stu[n];
    double average[n];
    int total[n];
    for (int j = 0; j < n; j++) {
        getchar();  //记得清楚换行符
        total[j] = 0;   //初始化
        gets(stu[j].name);
        gets(stu[j].id);
        for (int i = 0; i < 5; i++) {
            scanf("%d", &stu[j].score[i]);
            total[j] += stu[j].score[i];
        }
        average[j] = total[j] / 5.0;
        //sort(stu[j].score);
    }
    
    for (int j = 0; j < n; j++) {
        printf("Name:%s\n", stu[j].name);
        printf("ID:%s\n", stu[j].id);
        printf("Score:%d %d %d %d %d\n", stu[j].score[0], stu[j].score[1], stu[j].score[2], stu[j].score[3], stu[j].score[4]);
        printf("average:%.2lf total:%d\n", average[j], total[j]);
        printf("\n");
    }

    return 0;
}