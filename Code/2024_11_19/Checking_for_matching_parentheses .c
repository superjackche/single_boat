#include <stdio.h>
#include <string.h>

int main(void)
{
    int indicator = 1;
    int a = 0, b = 0;
    char ch[101] = {0};
    scanf("%s", ch);
    int lens = strlen(ch);
    for (int i = 0; i < lens; i++)
    {
        if (ch[i] == '(')
        {
            a++;
            for (int j = i+1; j < lens; j++)
            {
                if (ch[j] == ')')
                {
                    indicator = 0;
                    break;
                }
                else if (ch[j] == '(')
                {
                    break;
                }
            }
        }
        else if (ch[i] == ')') b++;
    }

    if (a != b) indicator = 1;
    
    if (indicator == 0) printf("parentheses match!\n");
    if (indicator == 1) printf("parentheses do not match!\n");
}