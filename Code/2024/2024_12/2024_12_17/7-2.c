#include <stdio.h>
#include <string.h>

int sign_test(char ch) {
    char special_chars[] = "~!@#$%^&*()[]}{|<>?/.,:\"';";    
    for (int j = 0; special_chars[j] != '\0'; j++) {
        if (ch == special_chars[j]) {
            return 1; // 找到特殊符号
        }
    }
    return 0;
}
int main (void) {
    int n;
    scanf("%d", &n);
    getchar();
    while (n--) {
        char password[32];
        gets(password);
        int len = strlen(password);
        password[len] = '\0';
        if (len < 6) {
            printf("no\n");
            continue;
        }
        int sign[5] = {0};
        int num = 0;
        for (int i = 0; i < len && password[i] != '\0'; i++) {
            if (password[i] >= '0' && password[i] <= '9') sign[0]++;
            if (password[i] >= 'A' && password[i] <= 'Z') sign[1]++;
            if (password[i] >= 'a' && password[i] <= 'z') sign[2]++;
            if (sign_test(password[i]) == 1) sign[3]++;
        }
        
        for (int i = 0; i < 4; i++) {
            if (sign[i] > 0) num++;
        }

        if (num >= 3) printf("yes\n");
        else printf("no\n");
    }
}