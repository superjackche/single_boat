#include <stdio.h>
int main() {
    int x, n;
    int goods[6], own[6];
    int bought1 = 0;
    int bought2 = 0;
    int bought3 = 0;
    int bought4 = 0;
    int bought5 = 0;
    
    scanf("%d %d", &x, &n);
    for (int i = 0; i < n; i++) {
        int max = 0;

        scanf("%d %d %d %d %d", &goods[0], &goods[1], &goods[2], &goods[3], &goods[4]);


        for (int k = 0; k < 5; k++) {
            if (goods[k] > max && x >= goods[k]) {
                max = goods[k];
            }
        }

        if (x >= max) {
            x -= max;
            switch (max) {
                case 1:
                    bought1++;
                    break;
                case 2: 
                    bought2++;
                    break;
                case 3: 
                    bought3++;
                    break;
                case 4: 
                    bought4++;
                    break;
                case 5: 
                    bought5++;
                    break;
            }
        }
    }
    printf("%d %d %d %d %d\n", bought1, bought2, bought3, bought4, bought5);
    printf("%d", x);
}