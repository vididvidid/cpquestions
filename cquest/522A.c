/*
 * File: 522A.c
 * Author: vididvidid 
 * Created: 2026-07-26 20:04:42
 */

#include <stdio.h>
#include <string.h>

void solve() {
    int n, c = 1, m = 1, i, l;
    char a[30], b[30], w[30], u[205][30];
    int d[205];
    
    scanf("%d", &n);
    strcpy(u[0], "polycarp");
    d[0] = 1;
    
    while (n--) {
        scanf("%s %s %s", a, w, b);
        for (i = 0; a[i]; i++) if (a[i] >= 'A' && a[i] <= 'Z') a[i] += 32;
        for (i = 0; b[i]; i++) if (b[i] >= 'A' && b[i] <= 'Z') b[i] += 32;
        for (i = 0; i < c; i++) {
            if (!strcmp(u[i], b)) {
                l = d[i] + 1;
                break;
            }
        }
        strcpy(u[c], a);
        d[c++] = l;
        if (l > m) m = l;
    }
    
    printf("%d\n", m);
}
