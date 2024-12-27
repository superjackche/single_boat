#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_NAME 15
#define LOGIN "LOGIN"
#define LOGOUT "LOGOUT"

typedef struct {
    char name[MAX_NAME];
    int time;      // 登录次数
    int h, m, s;   // 最后登录时间
    int sign;      // 登录状态标记
} User;

// 比较函数
int compareUsers(const void *a, const void *b) {
    User *u1 = (User *)a;
    User *u2 = (User *)b;
    
    if(u1->time != u2->time) {
        return u2->time - u1->time;  // 登录次数降序
    }
    return strcmp(u1->name, u2->name); // 用户名字典序
}

int main() {
    int n;
    scanf("%d", &n);
    
    User users[MAX_USERS] = {0};
    int userCount = 0;
    
    // 处理每条日志
    for(int i = 0; i < n; i++) {
        int h, m, s;
        char name[MAX_NAME], operation[7];
        scanf("%d %d %d %s %s", &h, &m, &s, name, operation);
        
        if(strcmp(operation, LOGIN) == 0) {
            // 查找用户
            int found = 0;
            for(int j = 0; j < userCount; j++) {
                if(strcmp(users[j].name, name) == 0) {
                    users[j].h = h;
                    users[j].m = m;
                    users[j].s = s;
                    users[j].time++;
                    users[j].sign = 1;
                    found = 1;
                    break;
                }
            }
            
            // 添加新用户
            if(!found) {
                strcpy(users[userCount].name, name);
                users[userCount].h = h;
                users[userCount].m = m;
                users[userCount].s = s;
                users[userCount].time = 1;
                users[userCount].sign = 1;
                userCount++;
            }
        }
    }
    
    // 按要求排序
    qsort(users, userCount, sizeof(User), compareUsers);
    
    // 输出结果
    for(int i = 0; i < userCount; i++) {
        printf("%s %d %d %d %d\n", 
               users[i].name, users[i].time, 
               users[i].h, users[i].m, users[i].s);
    }
    
    return 0;
}