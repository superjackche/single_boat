#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort(char **stu, int n);

int main(){
    int n;
    scanf("%d", &n);

    // 分配指针数组
    char **stu = (char**)malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++){
        char temp[10001] = {'\0'};
        scanf("%s", temp);
        int len = strlen(temp) + 1; // +1 for '\0'
        stu[i] = (char*)malloc(len * sizeof(char));
        strcpy(stu[i], temp);
    }

    sort(stu, n);

    // 输出并释放内存
    for(int i = 0; i < n; i++){
        printf("%s\n", stu[i]);
        free(stu[i]);
    }
    free(stu);
    return 0;
}

void sort(char **stu, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            // 提取卓越徽章
            char temp1[11] = {'\0'};
            char temp2[11] = {'\0'};
            int num1 = 0, num2 = 0;
            
            // 提取第一个字符串的卓越徽章
            for(int k = 0; stu[j][k] != '\0'; k++){
                if(stu[j][k] >= 'A' && stu[j][k] <= 'E'){
                    temp1[num1++] = stu[j][k];
                }
            }
            
            // 提取第二个字符串的卓越徽章
            for(int k = 0; stu[j+1][k] != '\0'; k++){
                if(stu[j+1][k] >= 'A' && stu[j+1][k] <= 'E'){
                    temp2[num2++] = stu[j+1][k];
                }
            }
            
            // 比较规则
            int cmp = strcmp(temp2, temp1);
            if(cmp == 0){
                // 卓越徽章相同时比较原字符串
                cmp = strcmp(stu[j+1], stu[j]);
            }
            
            // 需要交换
            if(cmp > 0){
                char *temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
}