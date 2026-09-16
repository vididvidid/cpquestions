/*
 * File: 1271C.c
 * Author: vididvidid 
 * Created: 2026-09-16 21:46:39
 */

#include <stdio.h>

int main() {
    int n, sx, sy;
    if (scanf("%d %d %d", &n, &sx, &sy) != 3) return 0;
    
    int c_left = 0, c_right = 0, c_up = 0, c_down = 0;
    
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (x < sx) c_left++;
        if (x > sx) c_right++;
        if (y > sy) c_up++;
        if (y < sy) c_down++;
    }
    
    int max = c_left;
    int px = sx - 1;
    int py = sy;
    
    if (c_right > max) {
        max = c_right;
        px = sx + 1;
        py = sy;
    }
    if (c_up > max) {
        max = c_up;
        px = sx;
        py = sy + 1;
    }
    if (c_down > max) {
        max = c_down;
        px = sx;
        py = sy - 1;
    }
    
    printf("%d\n", max);
    printf("%d %d\n", px, py);
    
    return 0;
}
