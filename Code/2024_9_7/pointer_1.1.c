#include <stdio.h>
struct stu
{
    char name[20];
    int age;
    double score;
};//这里有一个分号；要注意
int main()
{
    struct stu s1 = {"zhangsan", 20, 98.5};
    printf("1 : %s %d %lf\n", s1.name, s1.age, s1.score);

    struct stu *ps = &s1;
    printf("2 : %s %d %lf\n", (*ps).name, (*ps).age, (*ps).score);

    printf("3 : %s %d %lf\n", ps->name, ps->age, ps->score);

    return 0;
}