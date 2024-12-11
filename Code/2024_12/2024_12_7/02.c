#include<stdio.h>
#include<string.h>

#define        MAXLEN        100

int    isPalindrome(char word[]);

int main()
{
    char    word[MAXLEN];

    scanf( "%s" , &word ) ;
    if (isPalindrome(word))
        printf( "%s is a palindrome.\n" , word ) ;
    else
        printf( "%s is not a palindrome.\n" , word ) ; 
    
    return 0;
}

int    isPalindrome(char word[])
{
    int k = strlen(word);
    int m = 0;
    for (int i = 0; i < k; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            m++;
        }
        else
        {
            word[i] = 0;
        }
    }

    if (m == 0)
    {
        word[0] = '\n';
        return 0;
    }
    char temp[m];
    int n = 0;
    for (int j = 0; j < k; j++)
    {
        if (word[j] != 0)
        {
            temp[n] = word[j];
            n++;
        }
    }
    temp[n] = '\0';

    strcpy(word, temp);
    
    for (int i = 0, j = strlen(word)-1; i < j; i++, j--)
    {
        if (word[i] != word[j])
        {
            return 0;
        }
    }
    return 1;
}