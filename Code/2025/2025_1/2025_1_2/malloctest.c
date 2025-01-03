#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = 1024 * 1024; // 从1MB开始
    size_t max_size = 0;
    void *ptr = NULL;
    
    while (1) {
        ptr = malloc(size);
        
        if (ptr == NULL) {
            printf("最大成功分配: %.2f MB\n", (double)max_size / 1024 / 1024);
            break;
        }
        
        free(ptr); // 释放本次分配的内存
        max_size = size;
        size += 1024 * 1024; // 每次增加1MB
        printf("当前测试: %.2f MB\n", (double)size / 1024 / 1024);
    }
    
    return 0;
}