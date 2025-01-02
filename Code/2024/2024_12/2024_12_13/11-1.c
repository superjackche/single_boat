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
    struct stu stu1;
    int total = 0;
    double average = 0;
    gets(stu1.name);
    gets(stu1.id);
    for (int i = 0; i < 5; i++) {
        scanf("%d", &stu1.score[i]);
        total += stu1.score[i];
    }
    average = total / 5.0;
    sort(stu1.score);
    printf("Name:%s\n", stu1.name);
    printf("ID:%s\n", stu1.id);
    printf("Score:%d %d %d %d %d\n", stu1.score[0], stu1.score[1], stu1.score[2], stu1.score[3], stu1.score[4]);
    printf("average:%.2lf total:%d\n", average, total);
    
    return 0;
}