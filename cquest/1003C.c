/*
 * File: 1003C.c
 * Author: vididvidid 
 * Created: 2026-10-31 22:27:44
 */

#include <stdio.h>

void solve() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return;
    
    int a[5005];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    double max_avg = 0.0;
    
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            int len = j - i + 1;
            if (len >= k) {
                double avg = (double)sum / len;
                if (avg > max_avg) {
                    max_avg = avg;
                }
            }
        }
    }
    
    printf("%.15f\n", max_avg);
}

int main() {
    solve();
    return 0;
}
