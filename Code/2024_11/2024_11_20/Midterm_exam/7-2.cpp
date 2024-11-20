#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calcRanks(int *w, int *r) {
    for (int i = 0; i < 6; ++i) {
        r[i] = 1;
        for (int j = 0; j < 6; ++j) {
            if (w[i] < w[j]) r[i]++;
        }
    }
}

int cmp(const void *a, const void *b) {
    return memcmp(a, b, 6 * sizeof(int));
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int all[] = {0, 1, 2, 3, 4, 5}, rem[4], idx = 0;
    for (int i = 0; i < 6; ++i) if (all[i] != a && all[i] != b) rem[idx++] = all[i];

    int res[720][6], total = 0, r[6];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (j == i) continue;
            for (int k = 0; k < 4; ++k) {
                if (k == i || k == j) continue;
                for (int l = 0; l < 4; ++l) {
                    if (l == i || l == j || l == k) continue;
                    int w[] = {a, b, rem[i], rem[j], rem[k], rem[l]};
                    calcRanks(w, r);
                    for (int m = 0; m < 6; ++m) res[total][m] = r[m];
                    total++;
                }
            }
        }
    }

    qsort(res, total, sizeof(res[0]), cmp);
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < 6; ++j) printf("%d%c", res[i][j], j < 5 ? ' ' : '\n');
    }

    return 0;
}