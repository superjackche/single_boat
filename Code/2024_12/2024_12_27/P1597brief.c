#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char ch[256] = {0};
    scanf("%s", ch);
    int vars[3] = {0}; // 0:a, 1:b, 2:c
    int len = strlen(ch);
    
    for(int i = 0; i < len - 4; i++){
        // 检查是否为赋值语句 [a|b|c]:=x;
        if( (ch[i]=='a' || ch[i]=='b' || ch[i]=='c') &&
            ch[i+1]==':' && ch[i+2]=='=' && ch[i+4]==';'){
                int idx = ch[i] - 'a'; // 0对应a, 1对应b, 2对应c
                char x = ch[i+3];
                
                if(x >= '0' && x <= '9'){
                    vars[idx] = x - '0'; // 赋值为数字
                }
                else if(x >= 'a' && x <= 'c'){
                    vars[idx] = vars[x - 'a']; // 赋值为另一个变量的值
                }
        }
    }
    
    printf("%d %d %d", vars[0], vars[1], vars[2]);
    return 0;
}