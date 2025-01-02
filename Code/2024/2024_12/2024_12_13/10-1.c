#include <stdio.h>

#define        MAX        48

int        getScore(char * s) ;

int main()
{
    char    input[MAX] ;
    int        score ;
    
    scanf("%s",input);
    score = getScore(input) ;
    printf("%d\n",score) ;

    return 0;
}

int        getScore(char * s) {
    int i = 0;
    int sum = 0;
    while (s[i] != '\0') {
        if (s[i] == 'W') sum += 3;
        if (s[i] == 'D') sum += 1;
        i++;
    }
    return sum;
}