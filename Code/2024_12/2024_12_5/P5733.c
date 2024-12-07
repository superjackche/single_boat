#include <stdio.h>
#include <string.h>
int main (void)
{
    char ch[101] = {0};
    scanf("%s", ch);
    int n = strlen(ch);
    for (int i = 0; i < n; i++)
    {
        if (ch[i] >= 'a' && ch[i] <= 'z')
        {
            ch[i] -= 'a' - 'A';
        }
    }
    printf("%s", ch);
}