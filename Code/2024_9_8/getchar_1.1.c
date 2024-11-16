#include <stdio.h>
int main()
{
    char password [20] = {0};
    printf("Enter your password: ");
    scanf("%s", password);
    printf("please make sure that your password (Y/N)\n");
    //清空缓冲区
    while (getchar() != '\n')
    {
        ;
    }
    int ch = getchar();
    if (ch == 'Y')
    {
        printf("OK\n");
    }
    else if(ch == 'N')
    {
        printf("Wrong\n");
    }
    else
    {
        printf("Wrong Input\n");
    }
    return 0;
}