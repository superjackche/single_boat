#include <stdio.h>

typedef struct {
    char name[20];
    int age;
    double score;
} Stu;

void practice(Stu *stu, int n) {
    for (int i = 0; i < n; i++) {
        stu[i].score *= 1.2;
        stu[i].age++;
        if (stu[i].score >= 600) {
            stu[i].score = 600;
        }
    }
    return;
}

int main() {
    int n;
    scanf("%d", &n);
    Stu stu[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %lf", stu[i].name, &stu[i].age, &stu[i].score);
    }

    practice(stu, n);

    for (int i = 0; i < n; i++) {
        printf("%s %d %.0lf\n", stu[i].name, stu[i].age, stu[i].score);
    }
    return 0;
}