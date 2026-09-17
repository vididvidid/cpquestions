/*
 * File: 1016B.c
 * Author: vididvidid 
 * Created: 2026-09-17 20:26:55
 */

#include <stdio.h>
#include <string.h>

int a[1005];
int pref[1005];
char s[1005], t[1005];

int main() {
    int n, m, q;
    if (scanf("%d %d %d", &n, &m, &q) != 3) return 0;
    
    scanf("%s", s);
    scanf("%s", t);

    for (int i = 1; i <= n - m + 1; i++) {
        int match = 1;
        for (int j = 0; j < m; j++) {
            if (s[i - 1 + j] != t[j]) {
                match = 0;
                break;
            }
        }
        a[i] = match;
    }

    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        
        if (r - m + 1 < l) {
            printf("0\n");
        } else {
            printf("%d\n", pref[r - m + 1] - pref[l - 1]);
        }
    }

    return 0;
}
