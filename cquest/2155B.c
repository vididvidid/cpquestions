/*
 * File: 2155B.c
 * Author: vididvidid 
 * Created: 2026-07-21 12:31:23
 */
/* n x n matrix
 * each cell contains directions: UP, DOWN, LEFT, RIGHT
 * each cell moves 1 cell in the direction
 * reach the arrow pointing outside of maze.
 * give the arrangement.. 
 *
 * n < 100, k < 1000
 *
 * ---------------------------------------------------------------
 *  observations:
 *  if k == n^2 - 1 => NO
 *  2 x 2
 *  UU
 *  RU
 *
 *  start by filling outer cells.. first.. 
 */
#include <stdio.h>
#include <string.h>

void solve()
{
    int n, k;
    scanf("%d %d", &n, &k);
    if (k == ( n * n - 1 )) 
    {
        printf("NO\n");
        return;
    }
    if (k > (n * n))
    {
        printf("NO\n");
        return;
    }

    char s[n + 1][n + 1];
    for (int i = 0; i < n; i++)
    {
        memset(s[i], 0, n + 1);
    }
    int l = (n * n) - k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (l > 0)
            {
                l--;
                /* printf("%d ",j); */
                if (i == 0 && j == 0) s[i][j] = 'R';
                else if (i == 0) s[i][j] = 'L';
                else s[i][j] = 'U';
            }
            else
            {
                s[i][j] = 'D';
            }
        }
        s[i][n] = '\0';
        /* printf("\n"); */
    }
    printf("YES\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", s[i]);
    }
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
