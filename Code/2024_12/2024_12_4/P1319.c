#include <stdio.h>
int main (void)
{
    int n, num;
    int sign = 0;
    int first = 0;
    int a = 0;
    scanf("%d", &n);
    int n2 = n*n;
    int ch[(n+1)*(n+1)];

    while (first != n2)
    {
        scanf("%d", &num);
        for (int i = first; i < first + num; i++)
        {
            ch[i] = sign;
        }
        if (sign != 1) sign = 1;
        else sign = 0;
        first += num;
    }

    for (int j = 0; j < n2; j++)
    {
        printf("%d", ch[j]);
        a++;
        if (a%n == 0) printf("\n");
    }
    
}