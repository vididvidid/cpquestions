/*
 * File: 2238A.c
 * Author: vididvidid 
 * Created: 2026-06-30 23:23:20
 */

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *x, const void *y) {
    return (*(int*)x - *(int*)y);
}

void solve() {
    int n;
    long long c;
    if (scanf("%d %lld", &n, &c) != 2) return;
    
    int a[105], b[105], a_sorted[105], b_sorted[105];
    long long sum_diff = 0;
    int valid_no_reorder = 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a_sorted[i] = a[i];
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        b_sorted[i] = b[i];
        if (a[i] < b[i]) {
            valid_no_reorder = 0;
        }
        sum_diff += (a[i] - b[i]);
    }
    
    qsort(a_sorted, n, sizeof(int), cmp);
    qsort(b_sorted, n, sizeof(int), cmp);
    
    int valid_reorder = 1;
    for (int i = 0; i < n; i++) {
        if (a_sorted[i] < b_sorted[i]) {
            valid_reorder = 0;
            break;
        }
    }
    
    long long ans = -1;
    
    if (valid_no_reorder) {
        ans = sum_diff;
    }
    
    if (valid_reorder) {
        long long cost_reorder = c + sum_diff;
        if (ans == -1 || cost_reorder < ans) {
            ans = cost_reorder;
        }
    }
    
    printf("%lld\n", ans);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
