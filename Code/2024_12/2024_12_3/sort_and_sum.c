#include <stdio.h>
#include <string.h>

void bubble_sort(int *num, int n)
{
    for (int i = 0; i < n; i++)
    {
        int sign = 0;
        for (int j = 0; j < n-i-1; j++)
        {
            if (num[j] < num[j+1])
            {
                int temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                sign = 1;
            }
        }
        if (sign == 0) return;
    }
}

int main (void)
{
    int n;
    int temp = 0;
    int ans = 0;
    scanf("%d", &n);
    int n0 = n/2;
    int num[100] = {0};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp);
        num[i] = temp/2;
    }
    bubble_sort(num, n);

    for (int j = 0; j < n0; j++)
    {
        ans += num[j];
    }

    printf("%d", ans);
}