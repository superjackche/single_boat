#include <stdio.h>
int main()
{
    char ch;
    scanf("%c", &ch);
    if(ch >= 'a' && ch <= 'z')
        printf("this is a lower_case letter");
    else if(ch >='A' && ch <= 'Z')
        printf("this is an upper_case letter");
    else if(ch >= '0' && ch <= '9')
        printf("this is a number");
    else
        printf("this is neither a letter nor a number");
    return 0;
}