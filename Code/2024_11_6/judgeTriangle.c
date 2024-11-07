#include<stdio.h>

int judgeTriangle(int,int,int) ; 

int main()
{
    int        a, b, c ;    

    scanf("%d%d%d",&a,&b,&c);
    
    switch(judgeTriangle(a,b,c))
    {
        case    -1    :    printf("It is not a triangle.\n") ;    break ;
        case    0    :    printf("It is a scalenous triangle.\n") ;    break ;
        case    1    :    printf("It is a right-angled triangle.\n") ;    break ;
        case    2    :    printf("It is an isosceles triangle.\n") ;    break ;
        case    3    :    printf("It is a equilateral triangle.\n") ;    break ;
    }
    
    return 0;
}

int judgeTriangle(int a,int b,int c) {
    int a2 = a * a, b2 = b * b, c2 = c * c;
    if (a + b > c && a + c > b && b + c > a) {
        if (a2 + b2 == c2 || a2 + c2 == b2 || b2 + c2 == a2) {
            return 1;
        } else if (a == b || b == c || a == c) {
            if (a == b && b == c) {
                return 3;
            } else {
                return 2;
            }
        } else {
            return 0;
        }
    } else return -1;
}