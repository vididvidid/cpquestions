/*
 * File: 1493B.c
 * Author: vididvidid 
 * Created: 2026-09-15 23:30:05
 */

#include <stdio.h>

int rev(int d) {
    if (d == 0) return 0;
    if (d == 1) return 1;
    if (d == 2) return 5;
    if (d == 5) return 2;
    if (d == 8) return 8;
    return -1;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int h, m;
        scanf("%d %d", &h, &m);
        int cur_h, cur_m;
        scanf("%d:%d", &cur_h, &cur_m);
        while (1) {
            int h1 = cur_h / 10;
            int h2 = cur_h % 10;
            int m1 = cur_m / 10;
            int m2 = cur_m % 10;
            
            int r_m2 = rev(m2);
            int r_m1 = rev(m1);
            int r_h2 = rev(h2);
            int r_h1 = rev(h1);
            
            if (r_m2 != -1 && r_m1 != -1 && r_h2 != -1 && r_h1 != -1) {
                int ref_h = r_m2 * 10 + r_m1;
                int ref_m = r_h2 * 10 + r_h1;
                if (ref_h < h && ref_m < m) {
                    printf("%02d:%02d\n", cur_h, cur_m);
                    break;
                }
            }
            
            cur_m++;
            if (cur_m == m) {
                cur_m = 0;
                cur_h++;
                if (cur_h == h) {
                    cur_h = 0;
                }
            }
        }
    }
    return 0;
}
