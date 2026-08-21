/*
 * File: 2253A.c
 * Author: vididvidid 
 * Created: 2026-08-21 22:44:28
 */
#include <stdio.h>

int main() {
    int t, n, i, x, p;

    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        x = n + 1;
        p = 1;

        for (i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                p = 0;
                break;
            }
        }

        printf("%s\n", p ? "YES" : "NO");
    }

    return 0;
}
