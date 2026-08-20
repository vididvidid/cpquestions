/*
 * File: 2254A.c
 * Author: vididvidid 
 * Created: 2026-08-20 12:07:15
 */

#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int a, b, c, x, y, z;
        scanf("%d%d%d", &a, &b, &c);

        x = a < b ? (a < c ? a : c) : (b < c ? b : c);
        z = a > b ? (a > c ? a : c) : (b > c ? b : c);
        y = a + b + c - x - z;

        printf("%d\n", y - x);
    }

    return 0;
}
