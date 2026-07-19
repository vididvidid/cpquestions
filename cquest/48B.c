/*
 * File: 48B.c
 * Author: vididvidid 
 * Created: 2026-07-19 13:27:21
 */

/*
 * you are given n x m grid of integers, where 1 reperesent a tree and 0 
 * represent an empty space. you need to find a sub-grid of dimensions a x b
 * or b x a that fits inside the n x m grid and contains the minimum possible 
 * sum of 1's 
 *
 */
#include <stdio.h>
#include <limits.h>

int check(int grid[55][55], int n, int m, int r, int c)
{
    if (r > n || c > m)
    {
        return INT_MAX;
    }

    int mn = INT_MAX;

    for (int i = 0; i <= n - r; i++)
    {
        for (int j = 0; j <= m - c; j++)
        {
            int cnt = 0;

            for (int ri = i; ri < i + r; ri++)
            {
                for (int ci = j; ci < j + c; ci++)
                {
                    cnt += grid[ri][ci];
                }
            }

            if (cnt < mn)
            {
                mn = cnt;
            }
        }
    }

    return mn;
}

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int grid[55][55];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &grid[i][j]);
        }
    }

    int a, b;
    scanf("%d %d", &a, &b);

    int ans1 = check(grid, n, m, a, b);
    int ans2 = check(grid, n, m, b, a);
    int ans = (ans1 < ans2) ? ans1 : ans2;
    printf("%d\n", ans);
}

int main()
{
    solve();
    return 0;
}
