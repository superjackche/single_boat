#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    
    int n;
    int num = 0;
    //define a binary array to store
    int ch[1001][5] = {0};

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &ch[i][1], &ch[i][2], &ch[i][3]);
        ch[i][4] = ch[i][1] + ch[i][2] + ch[i][3];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (abs(ch[i][1] - ch[j][1]) <= 5 &&
                abs(ch[i][2] - ch[j][2]) <= 5 &&
                abs(ch[i][3] - ch[j][3]) <= 5 &&
                abs(ch[i][4] - ch[j][4]) <= 10) num++;
        }
    }
    printf("%d", num);

    return 0;
}