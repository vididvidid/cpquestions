/*
 * File: 2247A.c
 * Author: vididvidid 
 * Created: 2026-08-05 04:07:35
 */

#include <stdio.h>

int main() {
    int t, n, i, x, s;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        s = 0;
        for (i = 0; i < n; i++) {
            scanf("%d", &x);
            s += x;
        }
        if (s % 4 == 0) puts("YES");
        else puts("NO");
    }
    return 0;
}
