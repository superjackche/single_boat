#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 9
#define MAX_STU 1000

typedef struct {
    char name[NAME_LEN];
    int score1, score2, score3;
    int sum;
} Stu;

typedef struct {
    char name1[NAME_LEN];
    char name2[NAME_LEN];
} Pair;

int compare_pairs(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    int cmp = strcmp(p1->name1, p2->name1);
    if (cmp) return cmp;
    return strcmp(p1->name2, p2->name2);
}

int main() {
    int n = 0;
    scanf("%d", &n);

    Stu stu[MAX_STU];
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", stu[i].name,
              &stu[i].score1, &stu[i].score2, &stu[i].score3);
        stu[i].sum = stu[i].score1 + stu[i].score2 + stu[i].score3;
    }

    // 最大可能对数
    int max_pairs = n * (n - 1) / 2;
    Pair *pairs = (Pair *)malloc(sizeof(Pair) * max_pairs);
    int pair_count = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (abs(stu[i].score1 - stu[j].score1) > 5) continue;
            if (abs(stu[i].score2 - stu[j].score2) > 5) continue;
            if (abs(stu[i].score3 - stu[j].score3) > 5) continue;
            if (abs(stu[i].sum - stu[j].sum) > 10) continue;
            if (strcmp(stu[i].name, stu[j].name) < 0) {
                strcpy(pairs[pair_count].name1, stu[i].name);
                strcpy(pairs[pair_count].name2, stu[j].name);
            } else {
                strcpy(pairs[pair_count].name1, stu[j].name);
                strcpy(pairs[pair_count].name2, stu[i].name);
            }
            pair_count++;
        }
    }

    if (pair_count > 0) {
        qsort(pairs, pair_count, sizeof(Pair), compare_pairs);
        for (int i = 0; i < pair_count; i++) {
            printf("%s %s\n", pairs[i].name1, pairs[i].name2);
        }
    }

    return 0;
}