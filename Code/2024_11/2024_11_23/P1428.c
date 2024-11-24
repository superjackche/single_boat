#include <stdio.h> 
int main(void) { 
    int ch[101] = {0};
    int n;
    
    scanf("%d", &n);
    for (int k = 0; k < n; k++)
    {
        scanf("%d", &ch[k]);
    }
    
    for (int i = 0; i < n; i++)
    {
        int num = 0;
        for (int j = 0; j < i; j++)
        {
            if (ch[i] > ch[j]) num++;
        }
        printf("%d ", num);  
    }
}