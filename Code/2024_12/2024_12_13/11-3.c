#include <stdio.h>
#define MAX 22

struct stu {
    char name[MAX];
    int total;
} ;

void sort(struct stu *students, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (students[j].total < students[j + 1].total) {
                // 交换两个结构体
                struct stu temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            } else if (students[j].total == students[j + 1].total) {
                if (strcmp(students[j].name, students[j+1].name) > 0) {
                    // 交换两个结构体
                    struct stu temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    struct stu stu[n];
    for (int i = 0; i < n; i++) {
        scanf("%s", &stu[i].name);
        scanf("%d", &stu[i].total);
    }
    sort (stu, n);  //传入整个结构体数组

    for (int i = 0; i < n; i++) {
        printf("Name:%s\n", stu[i].name);
        printf("total:%d\n", stu[i].total);
        printf("\n");
    }
}