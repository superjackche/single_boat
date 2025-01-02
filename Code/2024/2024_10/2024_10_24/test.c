#include <stdio.h>
int main() {
    int n;
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    while (scanf("%d", &n) != EOF && n != -1) {
/*mention:
成功读取并赋值：
如果 scanf 成功读取并赋值了一个或多个输入项，返回值将是这些输入项的数量。
例如，scanf("%d", &n) 成功读取一个整数，返回值为 1。

读取失败：
如果 scanf 未能读取任何输入项（例如，输入格式不匹配或输入流中包含非法字符），返回值将是 0。
例如，scanf("%d", &n) 尝试读取一个整数，但输入的是 "abc"，返回值为 0。

到达文件末尾（EOF）：
如果 scanf 在读取输入时到达文件末尾（例如，用户在终端输入结束后按下 Ctrl+D），返回值将是 EOF。EOF 是一个宏定义，通常表示为 -1。
例如，用户在终端输入结束后按下 Ctrl+D，scanf("%d", &n) 返回值为 -1。*/
        if (n > 0) {
            a++;
            d += n;
        } else if (n == 0) {
            b++;
        } else if (n < 0) {
            c++;
            e += n;
        }
    }
    printf("%d %d %d\n%d %d", a, b, c, d, e);
}