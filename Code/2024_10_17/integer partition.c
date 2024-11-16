#include <stdio.h>
int main(){
    int num, num1;
    int len = 1;
    scanf("%d", &num);
    num1 = num;
    while(num1 < 10){
        num1 /= 10;
        len++;
    }
    for(int i = 0; i < len; i++){
        printf("%d", num % 10);
        num /= 10;
        if(i != len - 1) printf(" ");
        else printf("\n");
    }
    printf("%d\n", len);
}