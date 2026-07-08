/*
 * File: 467B.c
 * Author: vididvidid 
 * Created: 2026-07-08 19:09:42
 */

#include <stdio.h>

void solve() {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return;
    
    int a[1005];
    for (int i = 0; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int diff = a[i] ^ a[m];
        int count = 0;
        while (diff > 0) {
            count += (diff & 1);
            diff >>= 1;
        }
        if (count <= k) {
            ans++;
        }
    }
    
    printf("%d\n", ans);
}

int main() {
    solve();
    return 0;
}
