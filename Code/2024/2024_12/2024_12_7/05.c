#include <stdio.h>
#include <string.h>

void bubble_sort (int *ch, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (ch[j] > ch[j+1])
            {
                int temp = ch[j];
                ch[j] = ch[j+1];
                ch[j+1] = temp;
            }
        }
    }
}

int main() {
    char encrypted[101], original[101];
    scanf("%s", encrypted);
    scanf("%s", original);

    int len1 = strlen(encrypted);
    int len2 = strlen(original);

    if (len1 != len2) {
        printf("NO\n");
        return 0;
    }

    int en[26] = {0};
    int or[26] = {0};
    for (int i = 0; i < len1; i++) {
        en[encrypted[i] - 'A']++;
    }
    for (int i = 0; i < len2; i++) {
        or[original[i] - 'A']++;
    }
    bubble_sort (en, 26);
    bubble_sort (or, 26);
    for (int i = 0; i < 26; i++) {
        if (en[i] != or[i]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    return 0;
}