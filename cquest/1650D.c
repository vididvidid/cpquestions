/*
 * File: 1650D.c
 * Author: vididvidid 
 * Created: 2026-08-18 22:34:55
 */

#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, a[2005], d[2005];
        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        int ok = 1;

        for (int i = n; i >= 1; i--) {
            int p = 0;

            for (int j = 1; j <= i; j++) {
                if (a[j] == i) {
                    p = j;
                    break;
                }
            }

            if (!p) {
                ok = 0;
                break;
            }

            d[i] = p % i;

            int b[2005];
            for (int j = 1; j <= i; j++)
                b[j] = a[j];

            for (int j = 1; j <= i; j++)
                a[j] = b[(j - 1 + d[i]) % i + 1];
        }

        if (!ok) {
            printf("-1\n");
            continue;
        }

        for (int i = 1; i <= n; i++)
            printf("%d ", d[i]);
        printf("\n");
    }

    return 0;
}
