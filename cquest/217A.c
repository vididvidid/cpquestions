/*
 * File: 217A.c
 * Author: vididvidid 
 * Created: 2026-07-30 21:06:50
 */

#include <stdio.h>

int x[105], y[105], v[105], n;

void f(int i) {
    v[i] = 1;
    for (int j = 0; j < n; j++) {
        if (!v[j] && (x[i] == x[j] || y[i] == y[j])) {
            f(j);
        }
    }
}

void solve() {
    if (scanf("%d", &n) != 1) return;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (!v[i]) {
            f(i);
            c++;
        }
    }
    printf("%d\n", c - 1);
}

int main() {
    solve();
    return 0;
}
