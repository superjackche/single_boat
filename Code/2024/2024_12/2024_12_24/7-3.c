#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int m;
    int *powers;
    int *mods;
} Emperor;

int compareEmperor(const void *a, const void *b) {
    Emperor *e1 = (Emperor *)a;
    Emperor *e2 = (Emperor *)b;
    
    int min_m = e1->m < e2->m ? e1->m : e2->m;
    
    // 按照单挑顺序比较
    for(int i = 0; i < min_m; i++) {
        if(e1->mods[i] != e2->mods[i]) {
            return e2->mods[i] - e1->mods[i];
        }
    }
    return e2->m - e1->m;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Emperor *emperors = (Emperor *)malloc(n * sizeof(Emperor));
    
    // 读取输入
    for(int i = 0; i < n; i++) {
        scanf("%d", &emperors[i].m);
        emperors[i].powers = (int *)malloc(emperors[i].m * sizeof(int));
        emperors[i].mods = (int *)malloc(emperors[i].m * sizeof(int));
        
        for(int j = 0; j < emperors[i].m; j++) {
            scanf("%d", &emperors[i].powers[j]);
            emperors[i].mods[j] = emperors[i].powers[j] % 101;
        }
    }
    
    // 按单挑规则排序君主
    qsort(emperors, n, sizeof(Emperor), compareEmperor);
    
    // 输出结果
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < emperors[i].m; j++) {
            printf("%d%c", emperors[i].powers[j], 
                   j == emperors[i].m - 1 ? '\n' : ' ');
        }
    }
    
    return 0;
}