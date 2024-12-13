//特别提醒：当执行更改学生成绩操作时，无论学生是否存在，你的程序都要读入那三个成绩。否则会影响后续的输入。
//不看题？？？？？我叫不你不看题！！！！！老是ac不了吧。。。。。
#include <stdio.h>
#include <string.h>

#define MAX 12
#define SUM 1001

struct student {
    char name[MAX];
    char id[MAX];
    int score[4];
    int valid; // 0 表示无效，1 表示有效
};

// 检查学生是否已存在
int student_exists(struct student *stu, int n, const char *id) {
    for (int i = 0; i < n; i++) {
        if (stu[i].valid == 1 && strcmp(id, stu[i].id) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_information(struct student *stu, int *n) {
    if (*n >= SUM) {
        printf("Student list is full\n");
        return;
    }
    char id[MAX];
    scanf("%11s", id);
    getchar(); // 清空输入缓冲区

    if (student_exists(stu, *n, id)) {
        printf("Students already exist\n");
        // 读取并丢弃姓名和成绩
        char name[MAX];
        int score1, score2, score3;
        scanf("%11s %d %d %d", name, &score1, &score2, &score3);
        return;
    }

    strcpy(stu[*n].id, id);
    scanf("%11s", stu[*n].name);
    getchar(); // 清空输入缓冲区
    scanf("%d %d %d", &stu[*n].score[0], &stu[*n].score[1], &stu[*n].score[2]);
    stu[*n].valid = 1;
    (*n)++;
    printf("Add success\n");
}

void delete_information(struct student *stu, int *n) {
    char id0[MAX];
    scanf("%11s", id0);
    getchar(); // 清空输入缓冲区
    for (int i = 0; i < *n; i++) {
        if (stu[i].valid == 1 && strcmp(id0, stu[i].id) == 0) {
            for (int j = i; j < *n - 1; j++) {
                stu[j] = stu[j + 1];
            }
            (*n)--;
            printf("Delete success\n");
            return;
        }
    }
    printf("Students do not exist\n");
}

void change_information(struct student *stu, int n) {
    char id0[MAX];
    scanf("%11s", id0);
    getchar(); // 清空输入缓冲区
    int score1, score2, score3;
    scanf("%d %d %d", &score1, &score2, &score3);
    //先读取三个成绩，再去检查是否存在此人，避免数据没有读取而溢出
    for (int i = 0; i < n; i++) {
        if (stu[i].valid == 1 && strcmp(id0, stu[i].id) == 0) {
            stu[i].score[0] = score1;
            stu[i].score[1] = score2;
            stu[i].score[2] = score3;
            printf("Update success\n");
            return;
        }
    }
    printf("Students do not exist\n");
}

void print_information(struct student *stu, int n) {
    char id0[MAX];
    scanf("%11s", id0);
    getchar(); // 清空输入缓冲区
    for (int i = 0; i < n; i++) {
        if (stu[i].valid == 1 && strcmp(id0, stu[i].id) == 0) {
            printf("Student ID:%s\n", stu[i].id);
            printf("Name:%s\n", stu[i].name);
            double average = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2]) / 3.0;
            printf("Average Score:%.1lf\n", average);
            return;
        }
    }
    printf("Students do not exist\n");
}

int main() {
    struct student stu[SUM] = {0};
    int n = 0; // 当前学生数量
    int choice;
    int time = 0;
    scanf("%d", &time);

    for (int j = 0; j < time; j++) {
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_information(stu, &n);
                break;
            case 2:
                delete_information(stu, &n);
                break;
            case 3:
                change_information(stu, n);
                break;
            case 4:
                print_information(stu, n);
                break;
            default:
                break;
        }
    }
    return 0;
}