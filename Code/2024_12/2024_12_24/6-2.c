#include<stdio.h>

//字符串转换函数，将source按规则转换后保存在target中
void    getCounts(char source[] , char target[] ) ;

int main()
{
    char    source[100000] , target[100];
    
    scanf( "%s" , source ) ;
    getCounts( source , target ) ;
    printf( "%s\n" , target ) ;
    
    return 0 ;
}

void    getCounts(char source[] , char target[] ) {
    int len = strlen(source);
    int temp[1024] = {0};
    for (int i = 0; i < len; i++) {
        temp[source[i]-'0']++;
    }

    for (int i = 0, j = 0; i < 10; i++) {
        if (temp[i] != 0) {
            int num = temp[i];
            int len2 = 0;
            while (num >= 1) {
                num /= 10;
                len2++;
            }
            num = temp[i];
            if (len2 > 1) {
                int k = 0;
                while (num >= 1) {
                    target[j+len2-k-1] = num%10+'0';
                    num /= 10;
                    k++;
                }
                j += len2;
                target[j++] = i+'0';
            } else {
                target[j] = temp[i]+'0';
                j += len2;
                target[j++] = i+'0';
            }
        }
    }
}