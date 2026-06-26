/*
 * File: 1105A.c
 * Author: vididvidid 
 * Created: 2026-06-26 23:04:09
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;
    
    int a[1005];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int min_cost = 2e9;
    int best_t = 1;

    for (int t = 1; t <= 100; t++) {
        int current_cost = 0;
        
        for (int i = 0; i < n; i++) {
            if (a[i] < t - 1) {
                current_cost += (t - 1) - a[i];
            } else if (a[i] > t + 1) {
                current_cost += a[i] - (t + 1);
            }
        }

        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_t = t;
        }
    }

    printf("%d %d\n", best_t, min_cost);
}

int main() {
    solve();
    return 0;
}
