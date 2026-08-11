/*
 * File: 2056B.c
 * Author: vididvidid 
 * Created: 2026-08-11 22:14:22
 */

#include <stdio.h>

int main() {
    int t, n, i, j, c;
    char s[1005][1005];
    int p[1005];
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%s", s[i]);
        }
        for (i = 0; i < n; i++) {
            c = 0;
            for (j = 0; j < n; j++) {
                if (i == j) continue;
                if (j < i && s[i][j] == '1') c++;
                if (j > i && s[i][j] == '0') c++;
            }
            p[c] = i + 1;
        }
        for (i = 0; i < n; i++) {
            printf("%d ", p[i]);
        }
        printf("\n");
    }
    return 0;
}
