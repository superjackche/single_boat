#include<stdio.h>
#include<string.h>

#define MAXLEN        32
int    isCycloneWord(char *word) ;

int main()
{
    char    word[MAXLEN];
    int        n , i ;
    
    scanf("%d" , &n) ;
    for(i = 0 ; i < n ; i++) 
    {
        scanf("%s" , word) ;
        if ( isCycloneWord(word) == 1 )
            printf("YES\n") ;
        else
            printf("NO\n") ;
    }
 
    return 0;
}

int    isCycloneWord(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len/2; i++) {
        char ch1 = word[i];
        char ch2 = word[len - i - 1];
        if (ch1 - ch2 > 0) {
            return 0;
        }
    }
    for (int i = 0; i < len/2; i++) {
        char ch1 = word[len-1-i];
        char ch2 = word[1+i];
        if (ch1 - ch2 > 0) {
            return 0;
        }
    }
    return 1;
}