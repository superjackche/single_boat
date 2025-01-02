#include <stdio.h>
#include <stdbool.h>

bool is_angle(int a, int b, int c) {
    if (a + b > c && a + c > b && b + c > a) {
        return true;
    }
    return false;
}

bool is_it(int num) {
    int digits[6]; 
    int count = 0; 
    

    while (num > 0) {
        int digit = num % 10;
        if (digit == 0) return false;
        digits[count++] = digit;
        num /= 10;
    }
    
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            int k = 6 - i - j - 1;
            
            int a = digits[0], b = digits[i], c = digits[j];
            int d = digits[1], e = digits[k == 1 ? 5 : k - 1], f = digits[6 - k - (k == 1)];
            
            if (b < a) {int temp = a; a = b; b = temp;}
            if (c < b) {int temp = b; b = c; c = temp;}
            if (b < a) {int temp = a; a = b; b = temp;}
            
            if (e < d) {int temp = d; d = e; e = temp;}
            if (f < e) {int temp = e; e = f; f = temp;}
            if (e < d) {int temp = d; d = e; e = temp;}
            
            if (is_angle(a, b, c) && is_angle(d, e, f)) {
                return true; 
            }
        }
    }
    
    return false; 
}

int main() {
    int l, r, count = 0;
    scanf("%d %d", &l, &r);
    
    for (int i = l; i <= r; ++i) {
        if (is_it(i)) {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}