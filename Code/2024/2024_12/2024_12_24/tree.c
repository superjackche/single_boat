#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function
#include <time.h>

// ANSI颜色码
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

// 树的高度
#define HEIGHT 10

// 清屏函数
void clearScreen() {
    printf("\033[2J\033[H");
}

int main() {
    srand(time(NULL));
    while(1) {
        clearScreen();
        for(int i = 1; i <= HEIGHT; i++) {
            // 打印空格
            for(int j = i; j < HEIGHT; j++) {
                printf(" ");
            }
            // 打印树叶和灯饰
            for(int k = 1; k <= (2*i-1); k++) {
                if(rand() % 5 == 0) { // 随机位置放置彩灯
                    int color = rand() % 6;
                    switch(color) {
                        case 0: printf(RED "*"); break;
                        case 1: printf(GREEN "*"); break;
                        case 2: printf(YELLOW "*"); break;
                        case 3: printf(BLUE "*"); break;
                        case 4: printf(MAGENTA "*"); break;
                        case 5: printf(CYAN "*"); break;
                    }
                }
                else {
                    printf("*");
                }
            }
            printf(RESET "\n");
        }
        // 打印树干
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < HEIGHT-1; j++) {
                printf(" ");
            }
            printf("|\n");
        }
        printf(" Merry Christmas!!!\n");
        usleep(1000000); // 暂停半秒
    }
    return 0;
}