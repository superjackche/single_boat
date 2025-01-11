#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    // 边界扩展
    char map[102][102] = {0};  // 使用固定大小数组
    char ans[102][102] = {0};
    
    // 读取地图
    getchar();  // 处理第一个换行符
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%c", &map[i][j]);
        }
        getchar();  // 处理每行末尾换行符
    }
    
    // 计算答案
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (map[i][j] == '*') {
                ans[i][j] = '*';
                continue;
            }
            
            // 统计周围地雷数
            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (map[i + dx][j + dy] == '*') {
                        count++;
                    }
                }
            }
            ans[i][j] = count + '0';
        }
    }
    
    // 输出结果
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%c", ans[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}