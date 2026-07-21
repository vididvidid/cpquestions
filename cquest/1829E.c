/*
 * File: 1829E.c
 * Author: vididvidid 
 * Created: 2026-07-21 19:30:41
 */

/*
 * Given an nxm grid of non-negative integers representing node weight
 * find the maximum sum of node weights among all connected component
 * formed by 4 directionally adjacent nodes with strictly positive 
 * weights.
 */

#include <stdio.h>
#include <stdlib.h>

int dfs(int r, int c, int n, int m, int *a)
{
    if (r < 0 || r >= n || c < 0 || c >= m) return 0;

    int idx = r * m + c;

    if (a[idx] == 0) return 0;

    int vol = a[idx];
    a[idx] = 0;

    vol += dfs(r + 1, c, n, m, a);
    vol += dfs(r - 1, c, n, m, a);
    vol += dfs(r, c + 1, n, m, a);
    vol += dfs(r, c - 1, n, m, a);

    return vol;
}

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int *a = (int *)malloc(n * m * sizeof(int));

    for (int i = 0; i < n * m; i++)
    {
        scanf("%d", &a[i]);
    }

    int mx = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i * m + j] > 0)
            {
                int curr = dfs(i, j, n, m, a);
                if (curr > mx)
                {
                    mx = curr;
                }
            }
        }
    }

    printf("%d\n", mx);
    free(a);
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
