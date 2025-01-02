#include <stdio.h>
#include <string.h>

int main (void)
{
    char ch[101] = {0};
    int ans[256] = {0};
    scanf("%s", &ch);

    for (int i = 0; i < strlen(ch); i++)
    {
        if ((ch[i] >= 'A' && ch[i] <= 'Z') || (ch[i] >= 'a' && ch[i] <= 'z'))
        {
            ans[ch[i]]++;
        }
    }

    for (int j = 0; j < 256; j++)
    {
        if (ans[j] != 0)
            printf("The character %c has presented %d times.\n", j, ans[j]);
    }

    return 0;
}