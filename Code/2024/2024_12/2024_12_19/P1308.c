#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXN 1000001

int main(void) {
    char word[11];
    char article[MAXN];

    // 读取输入
    scanf("%s", word);
    getchar(); // 清除缓冲区中的换行符
    fgets(article, sizeof(article), stdin);

    int len0 = strlen(word);
    int len = strlen(article);
    // 去除末尾的换行符
    word[strcspn(word, "\n")] = '\0';
    article[strcspn(article, "\n")] = '\0';

    // 转换为小写
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
    
    int word_num = 0;
    int first_word = -1;
    int show_time = 0;
    int end_num = 0;
    int num = 0;
    int sign = 0;

    while (num < len) {
        while(num < len && article[num] == ' ') {
            num++;
            word_num = num;
        }
        if(num >= len) break;
        
        int start = num;

        for (; article[num] != ' '; num++) {
            article[num] = tolower(article[num]);
        }

        if (num - start != len0) continue;
        if (strncmp(&article[start], word, len0) == 0) {
            if (first_word == -1) {
                first_word = word_num;
            }
            show_time++;
        }
    }

    if (show_time != 0) {
        printf("%d %d", show_time, first_word);
    } else printf("-1");
    
    return 0;
}