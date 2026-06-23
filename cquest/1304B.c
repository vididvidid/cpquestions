/*
 * File: 1304B.c
 * Author: vididvidid 
 * Created: 2026-06-23 22:42:23
 */

#include <stdio.h>
#include <string.h>

void solve() {
    int n, m;
    scanf("%d %d", &n, &m);

    char s[105][55];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s[i]);
    }

    int used[105] = {0};
    int lidx[105];
    int ridx[105];
    int pair = 0;

    int midx = -1;

    for (int i = 0; i < n; i++)
    {
        if (used[i]) continue;

        for (int j = i + 1; j < n; j++) {
            if (used[j]) continue;

            int is_rev = 1;
            for (int k = 0; k < m; k++)
            {
                if (s[i][k] != s[j][m - 1 - k]) {
                    is_rev = 0;
                    break;
                }
            }        

            if (is_rev) {
                lidx[pair] = i;
                ridx[pair] = j;
                pair++;
                used[i] = 1;
                used[j] = 1;
                break;
            }
        }

        if (!used[i] && midx == -1)
        {
            int is_pal = 1;
            for (int k = 0; k < m / 2; k++)
            {
                if (s[i][k] != s[i][m - 1 - k]) {
                    is_pal = 0;
                    break;
                }
            }

            if (is_pal) {
                midx = i;
                used[i] = 1;
            }
        }
    }

    int tlen = pair * 2 *m;
    if (midx != -1) {
        tlen += m;
    }

    printf("%d\n", tlen);

    for (int i = 0; i < pair; i++) {
        printf("%s", s[lidx[i]]);
    }

    if (midx != -1)
    {
        printf("%s", s[midx]);
    }

    for (int i = pair - 1; i >= 0; i--) {
        printf("%s", s[ridx[i]]);
    }

    printf("\n");
}

int main() {
    solve();
    return 0;
}
