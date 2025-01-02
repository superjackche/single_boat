#include <stdio.h>

int Degree_of_liking(int x) {
    int i = 0;
    if (x % 2 == 0) i++;
    if (x > 4 && x <= 12) i++;
    return i;
}

int main(){
    int x = 0;
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d", &x);
    int i = Degree_of_liking(x);
    if (i == 0) d++;
    if (i == 1) c++;
    if (i == 1 || i == 2) b++;
    if (i == 2) a++;
    printf("%d %d %d %d", a, b, c, d);
    return 0;
}