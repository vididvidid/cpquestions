/*
 * File: 2025C.c
 * Author: vididvidid 
 * Created: 2026-08-14 23:00:31
 */

#include <stdio.h>
#include <stdlib.h>

int a[200005], u[200005], c[200005];

int cmp(const void *x, const void *y) {
    return (*(int*)x > *(int*)y) - (*(int*)x < *(int*)y);
}

void solve() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    qsort(a, n, sizeof(int), cmp);
    
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
