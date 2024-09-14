#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//生成菜单
void menu()
{
    printf("****************************\n");
    printf("****************************\n");
    printf("*         1.play           *\n");
    printf("*         2.exit           *\n");
    printf("****************************\n");
    printf("****************************\n");
}
void game()
{
    int random_num = rand() %100 + 1;
    int guess_num = 0;
    
    printf("please guess the number:\n");
    scanf("%d", &guess_num);
    
    while(guess_num != random_num)
    {
        if(guess_num > random_num)
        {
            printf("too big\n");
        }
        else if(guess_num < random_num)
        {
            printf("too small\n");
        }
        printf("please guess again:\n");
        scanf("%d", &guess_num);
    }
    printf("yes!!!u are right!u are so great my sweetheart\nlet's play another round!\n");
}
int main()
{
    int i = 0;
    int n = 0;
    srand((unsigned int)time(NULL));

    do
    {
        menu();
        printf("please choose your option:\n");
        scanf("%d", &i);
        if(n == 3)
        {
            printf("all right,it seems that u really want to quit\ngoodbye\n");
            break;
        }
        switch(i)
        {
            case 1:
                game();
                break;
            case 2:
                printf("please don't leave...\ni give u a chance again\n");
                n ++;
            default:
                printf("wrong input\nplease try again\n");
        }
    }while(i >= 1 && i <= 2 );
    
    return 0;
}