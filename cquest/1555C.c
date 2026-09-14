/*
 * File: 1555C.c
 * Author: vididvidid 
 * Created: 2026-09-14 22:26:39
 */

/*
 * Grid is 2 rows, M cols.
 * alice walks from top-left to bottom-right. she takes coins.
 * bob walks same path after alice. he takes left over coins.
 * bob wants max coins. alice wants bob to get min coins.
 * what is bob's score?
 *
 * there are only 2 rows. alice just chooses a column 'i' to drop to
 * row 2.
 * when alice drops at col 'i', she wipes out row 1 up to 'i', and row 2 after
 * 'i'.
 * bob is forced to take either:
 * - top row coins after col 'i'
 * - bottom row coins before col 'i'
 * bob will just pick the bigger of these two.
 * so we just use a running sum (prefix sum). test every drop column 'i' for
 * alice, find what bob gets, and keep the minium of those answers. super fast
 */

#include <stdio.h>

void solve()
{
    int m;
    scanf("%d", &m);

    int a[2][100005];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    long long sum_top = 0;
    long long sum_bottom = 0;

    for (int j = 0; j < m; j++)
    {
        sum_top += a[0][j];
    }

    long long best_bob_score = -1;

    for (int i = 0; i < m; i++) 
    {
        sum_top -= a[0][i];

        long long current_bob_score = sum_top > sum_bottom ? sum_top : sum_bottom;

        if (best_bob_score == -1 || current_bob_score < best_bob_score) {
            best_bob_score = current_bob_score;
        }

        sum_bottom += a[1][i];
    }

    printf("%lld\n", best_bob_score);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
