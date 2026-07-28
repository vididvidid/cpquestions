/*
 * File: 344B.c
 * Author: vididvidid 
 * Created: 2026-07-28 22:52:17
 */

#include <stdio.h>

void solve() {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) return;
    int s = a + b + c;
    if (s % 2 != 0 || s < 2 * a || s < 2 * b || s < 2 * c) {
        printf("Impossible\n");
        return;
    }
    s /= 2;
    printf("%d %d %d\n", s - c, s - a, s - b);
}

int main()
{
    solve();
    return 0;
}
