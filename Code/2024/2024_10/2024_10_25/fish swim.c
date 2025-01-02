#include <stdio.h>
int main(){
    int hour1, second1, hour2, second2, hour0, second0;
    scanf("%d %d %d %d",&hour1, &second1, &hour2, &second2);
    if (second2 > second1) {
        hour0 = hour2 - hour1;
        second0 = second2 - second1;
    } else if (second2 < second1) {
        hour0 = hour2 - hour1 - 1;
        second0 = second2 - second1 + 60;
    } else {
        hour0 = hour2 - hour1;
        second0 = 0;
    }
    printf("%d %d", hour0, second0);
    return 0;
}