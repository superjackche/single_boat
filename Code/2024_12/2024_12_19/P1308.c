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

    // 去除末尾的换行符
    word[strcspn(word, "\n")] = '\0';
    article[strcspn(article, "\n")] = '\0';

    // 转换为小写
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
    for (int i = 0; article[i]; i++) {
        article[i] = tolower(article[i]);
    }

    int word_len = strlen(word);
    int art_len = strlen(article);
    int count = 0;
    int first_pos = -1;
    int curr_pos = 0;
    int word_pos = 0; // 单词位置，从 0 开始计数

    // 在文章中查找单词
    while (curr_pos < art_len) {
        // 跳过空格
        while (curr_pos < art_len && article[curr_pos] == ' ') curr_pos++;
        if (curr_pos >= art_len) break;

        // 检查是否匹配目标单词
        if (strncmp(article + curr_pos, word, word_len) == 0 &&
            (article[curr_pos + word_len] == ' ' || article[curr_pos + word_len] == '\0') &&
            (curr_pos == 0 || article[curr_pos - 1] == ' ')) {
            // 匹配成功
            count++;
            if (first_pos == -1) {
                first_pos = word_pos;
            }
        }

        // 移动到下一个单词
        while (curr_pos < art_len && article[curr_pos] != ' ') curr_pos++;
        word_pos++; // 单词位置加 1
    }

    // 输出结果
    if (count > 0) {
        printf("%d %d", count, first_pos);
    } else {
        printf("-1");
    }

    return 0;
}