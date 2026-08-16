/*
 * File: 1846E1.c
 * Author: vididvidid 
 * Created: 2026-08-16 21:46:07
 */

#include <stdio.h>

void solve() {
    int n;
    scanf("%d", &n);

    for (int k = 2; k * k <= n; k++) {
        long long s = 1, p = 1;

        while (s < n) {
            p *= k;
            s += p;
            if (s == n) {
                printf("YES\n");
                return;
            }
            if (p > n) break;
        }
    }

    printf("NO\n");
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}
