#include <stdio.h>
#include <string.h>

int main() {
    char ch[300] = {'\0'};
    scanf("%s", ch);
    char a = '0';
    char b = '0';
    char c = '0';
    int len = strlen(ch);

    for (int i = 0; i < len-4; i++) {
        if (ch[i] == 'a' && ch[i+1] == ':' && ch[i+2] == '=' && ch[i+4] == ';') {
            char temp = ch[i+3];
            if (temp == 'a') temp = a;
            else if (temp == 'b') temp = b;
            else if (temp == 'c') temp = c;
            a = temp;
            continue;
        }
        if (ch[i] == 'b' && ch[i+1] == ':' && ch[i+2] == '=' && ch[i+4] == ';') {
            char temp = ch[i+3];
            if (temp == 'a') temp = a;
            else if (temp == 'b') temp = b;
            else if (temp == 'c') temp = c;
            b = temp;
            continue;
        }
        if (ch[i] == 'c' && ch[i+1] == ':' && ch[i+2] == '=' && ch[i+4] == ';') {
            char temp = ch[i+3];
            if (temp == 'a') temp = a;
            else if (temp == 'b') temp = b;
            else if (temp == 'c') temp = c;
            c = temp;
            continue;
        }
    }
    
    printf("%c %c %c", a, b, c);
    return 0;
}