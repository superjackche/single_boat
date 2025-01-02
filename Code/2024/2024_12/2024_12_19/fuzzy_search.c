#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXN 100001

int count_str(char *str, char *need);

int main(void) {
    char str[11];
    char article[MAXN];
    scanf("%s", str);
    getchar();
    fgets(article, sizeof(article), stdin);
    
    int len1 = strlen(str);
    int len2 = strlen(article);

    for (int i = 0; i < len1; i++) {
        str[i] = tolower(str[i]);
    }
    for (int j = 0; j < len2; j++) {
        article[j] = tolower(article[j]);
    }

    char *dest = strstr(article, str);
    if (dest == NULL) {
        printf("-1\n");
        return 0;
    } else {
        int ans2 = (int)(dest - article);
        int ans1 = count_str(article, str);
        printf("%d %d\n", ans1, ans2);
    }
}

int count_str(char *str, char *need) {
    int count = 0;
    char *found;
    while ((found = strstr(str, need)) != NULL) {
        count++;
        str = found + strlen(need);
    }
    return count;
}