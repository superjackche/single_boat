#include <stdio.h>
int main (void)
{
    char ch[11][1024] = {0};
    int num = 0;
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%s", ch[i]);
    }

    while (n--)
    {
        scanf("%d", &num);
        printf("%s\n", ch[num]);
    }

    return 0;
}