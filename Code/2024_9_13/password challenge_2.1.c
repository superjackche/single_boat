#include <stdio.h>
#include <unistd.h>
int main()
{
    char password[20] = {0}; 
    int attempt_count = 0;
    int i = 0;
    int n = 0;
    
    while(attempt_count <= 9)
    {
        for(i = 0; i < 3; i++)
        {
            printf("please enter your password:\n");
            scanf("%20s", password);
            attempt_count ++;
            //if(password =="iloveuforever")//error
            if(strcmp(password, "iloveuforever") == 0)
            {
                printf("your password is correct,and i really really really lbove u,my sweetheart\n");
                attempt_count ++;
                break;
            }
            else
            {
                printf("your password is wrong,please try again\n");
            }
        }
        if(attempt_count >= 3)
        {
            printf("u entered incorrect password for three times,so u have been locked out of the system\nplease wait for a while\n");
            for(n = 0; n <= 10; n++)
            {
                printf("please wait for %d seconds\n", n);
                sleep(1);
            }
            printf("u are now unlocked\n");
        }
        printf("u have entered incorrect password for %s times,so u have been locked out of the system\nplease connect the admin for help\n", attempt_count);
    }
    return 0;
}