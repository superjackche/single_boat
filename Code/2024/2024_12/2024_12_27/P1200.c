#include <stdio.h>
#include <string.h>

int main() {
    char star[20] = {'\0'};
    char team[20] = {'\0'};
    long long star_num = 1;
    long long team_num = 1;
    //这里要注意起始值必须为1，要是0的话所有的数乘出来都是0了....
    //问：我是怎么错的？。。。。。。。。

    scanf("%s", star);
    scanf("%s", team);

    for (int i = 0; i < strlen(star); i++) {
        star_num *= star[i] - 'A' + 1;
    }

    for (int i = 0; i < strlen(team); i++) {
        team_num *= team[i] - 'A' + 1;
    }

    star_num %= 47;
    team_num %= 47;

    if (star_num == team_num) {
        printf("GO");
    } else {
        printf("STAY");
    }

    return 0;
}