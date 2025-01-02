#include <stdio.h>
#include <string.h>

char *locatesubstr(char *str1,char *str2);
int main()
{
    char str1[505],str2[505];
    char *p;
    gets(str1);
    gets(str2);
    p=locatesubstr(str1,str2);
    
    if(p==NULL)    printf("NULL!\n");
    else    puts(p);
    
    return 0;
}

char *locatesubstr(char *str1,char *str2)
{
    int m = strlen(str1);
    for (int i = 0; i < m; i++)
    {
        int n = strlen(str2);
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (*(str1+i+j) == *(str2+j)) count++;
        }
        if (count == n) return str1 + i;
    }
    return NULL;
}