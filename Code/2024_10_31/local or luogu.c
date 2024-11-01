#include <stdio.h>
int main(){
    int n = 0;
    scanf("%d", &n);
    if (n <= 5) printf("Local");
    else if (n > 5) printf("Luogu");
    return 0;
}