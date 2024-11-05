#include <stdio.h>
int main(){
    char isbn[13] = {"123456789X"};
    long long sum = 0;
    int j = 1;

    scanf("%s", &isbn);
    for (int i = 0; i < 12; i++) {
        if (isbn[i] == '-') {
            continue;
        } else {
            sum += j * (isbn[i] - '0');
            j++;
        }
    }

    int last = sum % 11;
    if (last == 10) {
        last = 'X';
        if (isbn[12] == last) {
            printf("Right");
        } else {
            isbn[12] = last;
            printf("%s", isbn);
        }
    } else {
        if (isbn[12] == last + '0') {
            printf("Right");
        } else {
            isbn[12] = last + '0';
            printf("%s", isbn);
        }
    }

    return 0;
}