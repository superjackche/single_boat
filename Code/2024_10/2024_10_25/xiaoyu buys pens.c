#include <stdio.h>
#include <math.h>
int main(){
    int a, b, num;
    scanf("%d %d", &a, &b);
    num = floor((a*10 + b)/19);
    printf("%d", num);
    return 0;
}
/*floor()函数 向下取整
  ceil()函数 向上取整
  round()函数 四舍五入取整*/