#include <stdio.h>
char tell(int sum)
{
    int shipping_cost;
    if (sum < 20) 
    {
        shipping_cost = 10;
    }
    else if (sum >= 20 && sum < 30) 
    {
        shipping_cost = 8;
    } 
    else if (sum >= 30 && sum < 40)
    {
        shipping_cost = 5;
    } else
    {
        shipping_cost = 0;  // °üÓÊ
    }
}
int main()
{
    int a, b, c, d, e;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    e = a + b + c + d;
    printf("%d", tell(e));
    return 0;
}