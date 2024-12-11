#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOTAL_LENGTH 100000
#define MAX_STRINGS 100

void sort(char **p, int n);

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // 吃掉换行符

    char str[MAX_TOTAL_LENGTH];
    char *p[MAX_STRINGS];
    int k = 0;

    for (int i = 0; i < n; i++) {
        p[i] = &str[k];
        gets(&str[k]);
        int len = strlen(&str[k]);
        k += len;
        str[k++] = '\0';
    }

    sort(p, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", p[i]);
    }
    
    return 0;
}

void sort(char **p, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(p[j], p[j + 1]) > 0) {
                char *temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}