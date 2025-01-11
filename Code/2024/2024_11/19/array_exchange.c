#include <stdio.h>

void swap(int *a, int *b);


int main(void)
{
    int n;
    scanf("%d", &n);
    int A[11] = {0};
    int B[11] = {0};
    for (int a = 0; a < n; a++)
    {
        scanf("%d", &A[a]);
    }
    for (int a = 0; a < n; a++)
    {
        scanf("%d", &B[a]);
    }

    for (int i = 0; i < n; i++)
    {
        int x = B[i];
        swap(&A[x], &A[i]);
    }
    for (int j = 0; j < n-1; j++)
    {
        printf("%d ", A[j]);
    }
    printf("%d\n", A[n-1]);
    return 0;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}