/*已知一个英文单词，该单词中只包含大写字母“A—Z”与小写字母“a—z”。你的任务是将英文单词翻译成密码文。翻译规则是把所有字母用它后面的第三个字母替换，并假设字符a接在字符z后面，字符A接在字符Z后面。例如：zero将被翻译成chur。

输入格式:
只有一行，为一个长度不超过100，只包含英文大小写字母的字符串（以回车换行符‘\n’结尾）。

输出格式:
只有一行，为对应字符串的密码文。*/
#include <stdio.h>
int main(){
    int ch;
    int i = 0;
    ch = getchar();
    while (ch != '\n' && i <= 100) {
        if ((ch >= 'A' && ch <= 'W')||(ch >= 'a' && ch <= 'w') ) {
            ch = ch + 3;
            printf("%c", ch);
        } else if (ch == 'X'||ch =='Y'||ch == 'Z'||ch == 'x'||ch =='y'||ch == 'z') {
            ch = ch - 23;
            printf("%c", ch);
        } ch = getchar();
        i++;
    }
    return 0;

}