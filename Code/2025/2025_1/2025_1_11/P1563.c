#include <stdio.h>
int main (){
    int n, m;
    scanf("%d %d", &n, &m);
    int towards[n];
    char career[n][11];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 11; j++) {
            career[i][j] = '\0';
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &towards[i]);
        scanf("%s", &career[i]);
        getchar();
    }
    int position = 0;
    //全局设定，以逆时针为正
    for (int i = 0; i < m; i++) {
        int temp1, temp2;
        scanf("%d %d", &temp1, &temp2);
        if (temp1 == 0) {   //turn left
            if (towards[position] == 0) {   //in
                position -= temp2;
            } else {    //out
                position += temp2;
            }
        } else {
            if (towards[position] == 0) {   //in
                position += temp2;
            } else {    //out
                position -= temp2;
            }
        }
        while (position < 0) position += n;
        position %= n;
    }
    printf("%s", career[position]);
}