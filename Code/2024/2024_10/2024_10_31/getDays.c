#include<stdio.h>

int    getDays(int,int) ;

int main()
{
    int    year, month ;
    
    scanf("%d%d",&year,&month);
    printf("There are %d days in month %d year %d.",getDays(year,month), month, year) ;

    return 0 ;    
}

int is_leapyear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int getDays(int year, int month) {
    int days = 0;
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days = 31;
            break;
        case 2:
            if (is_leapyear(year)) {
                days = 29;
            } else {
                days = 28;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        default:
            // 处理无效月份
            days = -1;
            break;
    }
    return days;
}