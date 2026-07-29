/*
 * File: 292B.c
 * Author: vididvidid 
 * Created: 2026-07-29 18:37:54
 */

#include <stdio.h>

int d[100005];

void solve() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        d[u]++;
        d[v]++;
    }
    
    int c1 = 0, c2 = 0, cn = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] == 1) c1++;
        else if (d[i] == 2) c2++;
        else if (d[i] == n - 1) cn++;
    }
    
    if (m == n - 1 && c1 == 2 && c2 == n - 2) {
        printf("bus topology\n");
    } else if (m == n && c2 == n) {
        printf("ring topology\n");
    } else if (m == n - 1 && c1 == n - 1 && cn == 1) {
        printf("star topology\n");
    } else {
        printf("unknown topology\n");
    }
}

int main() {
    solve();
    return 0;
}
