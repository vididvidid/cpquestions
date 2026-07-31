/*
 * File: 2241A.c
 * Author: vididvidid 
 * Created: 2026-07-31 20:52:42
 */

#include <stdio.h>

void solve() {
    int t, x, y;
    if (scanf("%d", &t) != 1) return;
    while (t--) {
        scanf("%d %d", &x, &y);
        if (x % y == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    solve();
    return 0;
}
