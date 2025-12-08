#include <stdio.h>

int main() {
    int i, j, k, n, m = 1, r = 1;
    int a[2][100] = {0};

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[0][i]);

    while (m <= n) {
        for (i = 0; i < n; i++) {
            if (a[1][i]) continue;
            k = i;
            for (j = i; j < n; j++)
                if (a[1][j] == 0 && a[0][j] < a[0][k])
                    k = j;
            a[1][k] = r++;
            m++;
            for (j = 0; j < n; j++)
                if (a[1][j] == 0 && a[0][j] == a[0][k]) {
                    a[1][j] = a[1][k];
                    m++;
                }
            break;
        }
    }

    for (i = 0; i < n; i++)
        printf("a[%d]=%d, %d", i, a[0][i], a[1][i]);

    return 0;
}