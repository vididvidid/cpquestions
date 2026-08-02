/*
 * File: 2236B.c
 * Author: vididvidid 
 * Created: 2026-08-02 19:12:19
 */
#include <stdio.h>
char s[200005];
int c[200005];
void solve()
{
    int n, k, i , o;
    scanf("%d %d %s", &n, &k, s);
    for(i = 0; i < k; i++) c[i] = 0;
    for(i = 0; i < n; i++) {
        if (s[i] == '1') c[i % k]++;
    }
    o = 1;
    for (i = 0; i < k; i++) {
        if (c[i] % 2) {
            o = 0;
            break;
        }
    }
    printf(o ? "YES\n" : "NO\n");
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
