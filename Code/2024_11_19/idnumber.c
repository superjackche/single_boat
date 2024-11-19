#include <stdio.h>
#include <string.h>

int check_id_card(const char *id_card) {
    int A[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    char check[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
    
    int total = 0;
    for (int i = 0; i < 17; i++) {
        total += (id_card[i] - '0') * A[i];
    }
    
    int remainder = total % 11;
    char expected_check_digit = check[remainder];
    
    return id_card[17] == expected_check_digit;
}

int main() {
    int T;
    scanf("%d", &T);
    
    char id_card[19] = {0}; // 18位身份证号码 + 1个终止符
    for (int i = 0; i < T; i++) {
        scanf("%s", id_card);
        if (check_id_card(id_card)) {
            printf("right\n");
        } else {
            printf("wrong\n");
        }
    }
    
    return 0;
}