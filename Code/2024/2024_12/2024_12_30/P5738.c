#include <stdio.h>
#include <stdlib.h>

double average_marks(int *s, int m);

int compare(const void *a, const void *b);

int main () {
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    double max = 0;
    for (int i = 0; i < n; i++) {
        int *score = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &score[j]);
        }
        double average = average_marks(score, m);
        if (average > max) {
            max = average;
        }
    }
    printf("%.2lf", max);
    return 0;
}

double average_marks(int *s, int m) {
    qsort(s, m, sizeof(int), compare);
    double sum = 0;
    for (int i = 1; i < m - 1; i++) {
        sum += s[i];
    }
    return sum / (m - 2) * 1.0;
}

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}