/*
 * File: 2025C.c
 * Author: vididvidid 
 * Created: 2026-08-14 23:00:31
 */
#include <stdio.h>

int a[200005], t_a[200005], u[200005], c[200005];

void ms(int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    ms(l, m);
    ms(m + 1, r);
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) t_a[k++] = a[i] < a[j] ? a[i++] : a[j++];
    while (i <= m) t_a[k++] = a[i++];
    while (j <= r) t_a[k++] = a[j++];
    for (i = l; i <= r; i++) a[i] = t_a[i];
}

void solve() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    ms(0, n - 1);
    
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (!i || a[i] != a[i-1]) {
            u[m] = a[i];
            c[m++] = 1;
        } else {
            c[m-1]++;
        }
    }
    
    int mx = 0, s = 0, l = 0;
    for (int r = 0; r < m; r++) {
        if (r > 0 && u[r] != u[r-1] + 1) {
            l = r;
            s = 0;
        }
        s += c[r];
        while (r - l + 1 > k) {
            s -= c[l++];
        }
        if (s > mx) {
            mx = s;
        }
    }
    printf("%d\n", mx);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
