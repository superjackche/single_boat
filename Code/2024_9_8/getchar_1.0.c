#include <stdio.h>
int main()
{
    char password [20] = {};
    printf("Enter your password: ");
    scanf("%s", password);
    printf("please make sure that your password (Y/N)\n");
    //清空缓冲区
    getchar();
    int ch = getchar();
    if (ch == 'Y')
    {
        printf("OK\n");
    }
    else
    {
        printf("Wrong\n");
    }
    return 0;
}