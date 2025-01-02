#include <stdio.h>

int findMax(int n) ;

int main()
{   
    int n ; 
    
    scanf("%d", &n); 
    printf("%d\n" , findMax( n ) ) ; 
    
    return 0;
}

int findMax(int n) {
    int temp;
    scanf("%d", &temp);
    if (n == 1) {
        return temp; 
    } else {
        // 取剩下 n-1 个数的最大值
        int num = findMax(n - 1);
        // 比较 temp 和子问题返回的最大值
        return (temp > num) ? temp : num;
    }
}