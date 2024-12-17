#include <stdio.h>
#include <string.h>




int main (void) {
    int n;
    scanf("%d", &n);
    int **score = (int **)malloc((n+1) * sizeof(int *));
    int student_count[n+1];
    int score_average[n+1];
    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        student_count[i] = m;
        score[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &score[i][j]);
        }
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += score[i][j];
        }
        score_average[i] = sum / m;
    }
    
    int index[n];
    for (int i = 0; i < n; i++) {
        index[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (score_average[index[j]] > score_average[index[j + 1]]) {
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        int idx = index[i];
        for (int j = 0; j < student_count[idx]; j++) {
            printf("%d", score[idx][j]);
            if (j < student_count[idx] - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}