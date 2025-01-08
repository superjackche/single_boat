#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort(char **stu, int n);

int main(){
    int n;
    scanf("%d", &n);

    char **stu = (char**)malloc(n*sizeof(char *));
    for (int i = 0; i < n; i++) {
        char temp[10001] = {'\0'};
        scanf("%s", temp);
        int len = strlen(temp);
        stu[i] = (char*)malloc(len*sizeof(char));
        strcpy(stu[i], temp);
    }

    sort(stu, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", stu[i]);
    }
}

void sort(char **stu, int n) {

    for (int m = 0; m < n; m++) {
        for (int k = 0; k < n - 1; k++) {
            int sign = 0;

            char temp11[11];
            char temp21[11];
            int num1 = 0;
            int num2 = 0;


            int len1 = strlen(stu[k]);
            int len2 = strlen(stu[k+1]);
            for (int i = 0; i < len1; i++) {
                if (stu[k][i] >= 'A' && stu[k][i] <= 'E') {
                    temp11[num1++] = stu[k][i];
                }
            }
            for (int i = 0; i < len2; i++) {
                if (stu[k][i] >= 'A' && stu[k][i] <= 'E') {
                    temp21[num2++] = stu[k][i];
                }
            }

            if (strcmp(temp11, temp21) == 0) {
                if (strcmp(stu[k], stu[k+1]) < 0) {
                    sign = 1;
                }
            } else if (strcmp(temp11, temp21) < 0) sign = 1;

            if (sign == 1) {
                char *tempkey = stu[k];
                stu[k] = stu[k+1];
                stu[k+1] = tempkey;
            }
        }
    }
}