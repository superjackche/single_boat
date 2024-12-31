#include <stdio.h>
#include <stdlib.h>

#define NAME 10
#define MAX 1001

int compare(const void *a, const void *b);

typedef struct {
    char name[NAME];
    int score1;
    int score2;
    int score3;
    double average;
    int id; // 新增字段，记录输入顺序
} Stu;

int compare(const void *a, const void *b) {
    Stu *s1 = (Stu *)a;
    Stu *s2 = (Stu *)b;

    if (s2->average > s1->average) return 1;
    if (s2->average < s1->average) return -1;
    // 平均分相同，比较 id
    if (s1->id < s2->id) return -1;
    if (s1->id > s2->id) return 1;
    return 0;
}

int main() {
    int n = 0;
    scanf("%d", &n);
    Stu stu[MAX] = {0};

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", stu[i].name, &stu[i].score1,
                            &stu[i].score2, &stu[i].score3);
        stu[i].average = (stu[i].score1 + stu[i].score2 + stu[i].score3) / 3.0;
        stu[i].id = i; // 记录输入顺序
    }

    qsort(stu, n, sizeof(Stu), compare);

    printf("%s %d %d %d", stu[0].name, stu[0].score1,
                          stu[0].score2, stu[0].score3);
    return 0;
}