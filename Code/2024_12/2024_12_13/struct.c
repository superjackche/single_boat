#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM1 30
#define NUM2 30

struct book {
    char bookname[NUM1];
    char writer[NUM2];
    double prize;
};

int main() {
    int n;
    printf("请输入书籍数量: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("输入的数量无效。\n");
        return 1;
    }

    // 动态分配内存存储n本书
    struct book *library = (struct book *)malloc(n * sizeof(struct book));
    if (library == NULL) {
        printf("内存分配失败。\n");
        return 1;
    }

    // 清空输入缓冲区
    while (getchar() != '\n');

    for (int i = 0; i < n; i++) {
        printf("请输入第%d本书的书名:\n", i + 1);
        if (fgets(library[i].bookname, NUM1, stdin) != NULL) {
            // 移除换行符
            library[i].bookname[strcspn(library[i].bookname, "\n")] = '\0';
        } else {
            printf("输入书名失败。\n");
            // 释放已分配的内存
            free(library);
            return 1;
        }

        printf("请输入第%d本书的作者:\n", i + 1);
        if (fgets(library[i].writer, NUM2, stdin) != NULL) {
            // 移除换行符
            library[i].writer[strcspn(library[i].writer, "\n")] = '\0';
        } else {
            printf("输入作者失败。\n");
            free(library);
            return 1;
        }

        printf("请输入第%d本书的价格:\n", i + 1);
        if (scanf("%lf", &library[i].prize) != 1) {
            printf("输入价格失败。\n");
            free(library);
            return 1;
        }

        // 清空输入缓冲区
        while (getchar() != '\n');
    }

    // 输出所有书籍信息
    printf("\n所有书籍信息:\n");
    for (int i = 0; i < n; i++) {
        printf("书名: %s\n作者: %s\n价格: %.2lf\n\n", library[i].bookname, library[i].writer, library[i].prize);
    }

    // 释放动态分配的内存
    free(library);

    return 0;
}