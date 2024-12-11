#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char **p, int n);

int main() {
    int n;
    scanf("%d", &n);
    getchar();

    char **p = (char **)malloc(n * sizeof(char *));
    if (p == NULL) return -1;

    char temp[1000];
    for (int i = 0; i < n; i++) {
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0'; // 去除换行符

        int len = strlen(temp);
        char *ch = (char *)malloc((len + 1) * sizeof(char));
        if (ch == NULL) return -1;
        
        strcpy(ch, temp);
        p[i] = ch;
    }

    sort(p, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", p[i]);
    }

    return 0;
}

void sort(char **p, int n) {
    // 使用冒泡排序对字符串数组进行排序
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