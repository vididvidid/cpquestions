/*
 * File: 1850F.c
 * Author: vididvidid 
 * Created: 2026-08-15 22:52:03
 */

#include <stdio.h>

int c[200005], s[200005];

void solve() {
    int n, i, j, x, m = 0;
    scanf("%d", &n);
    for(i = 1; i <= n; i++) {
        c[i] = 0;
        s[i] = 0;
    }
    for(i = 0; i < n; i++) {
        scanf("%d", &x);
        if(x <= n) {
            c[x]++;
        }
    }
    for(i = 1; i <= n; i++) {
        if(c[i]) {
            for(j = i; j <= n; j += i) {
                s[j] += c[i];
            }
        }
    }
    for(i = 1; i <= n; i++) {
        if(s[i] > m) {
            m = s[i];
        }
    }
    printf("%d\n", m);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        solve();
    }
    return 0;
}
