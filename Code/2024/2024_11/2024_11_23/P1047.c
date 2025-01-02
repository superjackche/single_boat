#include <stdio.h>
int main(void)
{
    int ch[10001] = {0};
    int l, m;
    int num = 0;
    scanf("%d %d", &l, &m);

    //initialize the length of trees
    for (int i = 0; i <= l; i++)
    {
        ch[i] = 1;
    }

    while (m--)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        //remove trees
        for (int j = a; j <= b; j++)
        {
            ch[j] = 0;
        }
    }

    //get&printf the number of trees
    for (int k = 0; k <= l; k++)
    {
        if (ch[k] == 1) num++;
    }
    printf("%d", num);

    return 0;
}