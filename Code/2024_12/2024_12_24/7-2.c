#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char bookname[60];
    int sale;
    int year;
    int month;
    int day;
    int price;
    int score;

} inf;

// 比较函数，根据综合排名规则排序
int compare(const void *a, const void *b) {
    inf *bookA = (inf *)a;
    inf *bookB = (inf *)b;

    // 1. 价格，低的优先
    if (bookA->price != bookB->price)
        return bookA->price - bookB->price;

    // 2. 出版时间，晚的优先
    if (bookA->year != bookB->year)
        return bookB->year - bookA->year;
    if (bookA->month != bookB->month)
        return bookB->month - bookA->month;
    if (bookA->day != bookB->day)
        return bookB->day - bookA->day;

    // 3. 销量，大的优先
    if (bookA->sale != bookB->sale)
        return bookB->sale - bookA->sale;

    // 4. 用户评分，高的优先
    return bookB->score - bookA->score;
}

int main() {
    int n;
    scanf("%d", &n);
    inf book[n];
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d %d %d %d", book[i].bookname, &book[i].sale, &book[i].year, &book[i].month, &book[i].day, &book[i].price, &book[i].score);
    }

    // 使用 qsort 进行排序
    qsort(book, n, sizeof(inf), compare);

    // 输出排序后的结果
    for (int i = 0; i < n; i++) {
        printf("%s %d %d %d %d %d %d\n", book[i].bookname, book[i].sale, book[i].year, book[i].month, book[i].day, book[i].price, book[i].score);
    }

    return 0;
}