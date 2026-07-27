/*
 * File: 370A.c
 * Author: vididvidid 
 * Created: 2026-07-27 21:14:41
 */

#include <stdio.h>
#include <stdlib.h>

void solve() {
    int a, b, c, d;
    if (scanf("%d %d %d %d", &a, &b, &c, &d) != 4) return;
    
    int r = (a == c || b == d) ? 1 : 2;
    
    int bi = 0;
    if ((a + b) % 2 == (c + d) % 2) {
        bi = (abs(a - c) == abs(b - d)) ? 1 : 2;
    }
    
    int x = abs(a - c);
    int y = abs(b - d);
    int k = (x > y) ? x : y;
    
    printf("%d %d %d\n", r, bi, k);
}

int main() {
    solve();
    return 0;
}
