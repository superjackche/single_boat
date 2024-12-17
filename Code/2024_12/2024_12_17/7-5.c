#include <stdio.h>

struct person {
    char name[12];
    int h, m, s;
};


void time_compare(int h, int m, int s, struct man person) {
    
}
int main (void) {
    int n;
    scanf("%d", &n);
    struct person man[n];
    for (int i = 0; i < n; i++) {
        char ch[100];
        gets(ch);
        int h, m, s;
        char temp_name, io;
        sscanf(ch, "%d %d %d %s %s", &h, &m, &s, &temp_name, &io);
        for (int i = 0; i < 101; i++) {
            if (strcmp(man[i].name, temp_name) == 0) {
                time_compare(h, m, s, man[i].h, man[i].m, man[i].s);
            }
        }
    }
}