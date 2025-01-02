#include<stdio.h>
#include<stdlib.h>

char ** create1(int n) ;
void create2( char ** strPtr , int n ) ;
void fill(char ** strPtr , int n) ;

int main()
{
    int        n, i;
    char**    strPtr ;

    scanf("%d", &n );
    strPtr = create1( n * 2 + 1 ) ;
    create2( strPtr ,  n * 2 + 1 ) ;
    fill(strPtr , n) ;

    for (i = 0; i < 2 * n + 1; i++)
    {
        printf("%s\n" , strPtr[i]);
    }
    
    for ( i = 0 ; i < n * 2 + 1 ; i++ )
        free(strPtr[i]) ;
    free(strPtr) ;

    return 0;
}

char ** create1(int n)
{
    char **strPtr = (char **)malloc(sizeof(char *) * n);
    if (strPtr != NULL) return strPtr;
    else return NULL;
}

void create2( char ** strPtr , int n )
{
    for(int i = 0; i < n; i++)
    {
        strPtr[i] = (char *)malloc(sizeof(char) * (n+1));
        if (strPtr[i] == NULL)
        {
            printf("内存分配失败！\n");
            exit(1);
        }
    }
}

void fill(char ** strPtr , int n)
{
    int size = 2 * n + 1;
    for(int i = 0; i < size; i++)
    {
        // 初始化字符串
        for(int j = 0; j < size; j++)
        {
            strPtr[i][j] = ' ';
        }
        

        if(i < n)
        {
            strPtr[i][n - i] = '/';
            strPtr[i][n + i] = '\\';
            strPtr[i][n+i+1] = '\0';
        }
        else if(i == n)
        {
            strPtr[i][0] = 'X';
            strPtr[i][size - 1] = 'X';
            strPtr[i][size] = '\0';
        }
        else
        {
            strPtr[i][i - n] = '\\';
            strPtr[i][(size - 1) - (i - n)] = '/';
            strPtr[i][size - (i - n)] = '\0';
        }

        strPtr[0][n] = 'X';
        strPtr[2*n][n] = 'X';
    }
}