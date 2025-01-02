#include <stdio.h>
int main()
{
    char a;
    short b;
    int c;
    long d;
    long long e;
    float f;
    double g;

    scanf("%c", &a);
    scanf("%hd", &b);
    scanf("%d", &c);
    scanf("%ld", &d);
    scanf("%lld", &e);
    scanf("%f", &f);
    scanf("%lf", &g);

    printf("The 'char' variable is %c, it takes %zu byte.\n", a, sizeof(a));
    printf("The 'short' variable is %hd, it takes %zu bytes.\n", b, sizeof(b));
    printf("The 'int' variable is %d, it takes %zu bytes.\n", c, sizeof(c));
    printf("The 'long' variable is %ld, it takes %zu bytes.\n", d, sizeof(d));
    printf("The 'long long' variable is %lld, it takes %zu bytes.\n", e, sizeof(e));
    printf("The 'float' variable is %.6lf, it takes %zu bytes.\n", f, sizeof(f));
    printf("The 'double' variable is %.6lf, it takes %zu bytes.", g, sizeof(g));

    return 0;
}