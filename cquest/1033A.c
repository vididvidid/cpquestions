/*
 * File: 1033A.c
 * Author: vididvidid 
 * Created: 2026-07-25 19:50:15
 */

#include <stdio.h>

void solve() {
    int n;
    int ax, ay;
    int bx, by;
    int cx, cy;
    
    if (scanf("%d", &n) != 1) return;
    scanf("%d %d", &ax, &ay);
    scanf("%d %d", &bx, &by);
    scanf("%d %d", &cx, &cy);
    
    int same_x_quadrant = ((bx < ax) == (cx < ax));
    int same_y_quadrant = ((by < ay) == (cy < ay));
    
    if (same_x_quadrant && same_y_quadrant) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    solve();
    return 0;
}
