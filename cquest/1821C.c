/*
 * File: 1821C.c
 * Author: vididvidid 
 * Created: 2026-08-17 23:38:26
 */

#include <stdio.h>
#include <string.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        char s[200005];
        scanf("%s", s);

        int n = strlen(s), ans = 100;

        for (char c = 'a'; c <= 'z'; c++) {
            int x = 0, m = 0;

            for (int i = 0; i < n; i++) {
                if (s[i] != c)
                    x++;
                else
                    x = 0;

                if (x > m)
                    m = x;
            }

            int k = 0;
            while (m) {
                m /= 2;
                k++;
            }

            if (k < ans)
                ans = k;
        }

        printf("%d\n", ans);
    }

    return 0;
}
