/*
 * File: 2246A.c
 * Author: vididvidid 
 * Created: 2026-08-06 22:08:02
 */

#include <stdio.h>

int main() {
    int t, n, i;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            printf("%d ", i % 2 ? i + 1 : i - 1);
        }
        printf("\n");
    }
    return 0;
}
