/*
 * File: 2250A.c
 * Author: vididvidid 
 * Created: 2026-08-03 19:59:47
 */
#include <stdio.h>
int main() {
    int t, n, i, w, l, r;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        l = -1;
        r = 2000000000;
        for (i = 0; i < n; i++) {
            scanf("%d", &w);
            if (i % 2 == 0) {
                if (w < r) r = w;
            } else {
                if (w > l) l = w;
            }
        }
        if (n % 2 != 0 || r - l < 2) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}
