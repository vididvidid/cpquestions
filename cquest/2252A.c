/*
 * File: 2252A.c
 * Author: vididvidid 
 * Created: 2026-08-22 23:04:32
 */

#include <stdio.h>

int main() {
    int t, n, a[55];

    scanf("%d", &t);

    while (t--) {
        int s = 0, mx = 0, x = 0;

        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            s += a[i];
        }

        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = 0; j < n; j++)
                if (a[i] == a[j])
                    c++;

            if (c > mx) {
                mx = c;
                x = a[i];
            }
        }

        if (mx <= (n + 1) / 2)
            printf("%d\n", s);
        else {
            int k = n - mx;
            printf("%d\n", s - mx * x + (k + 2) * x);
        }
    }

    return 0;
}
