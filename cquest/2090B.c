/*
 * File: 2090B.c
 * Author: vididvidid 
 * Created: 2026-05-25 17:02:59
 */

#include <stdio.h>
#include <stdbool.h>

void solve()
{
    int n, m;
    if (scanf("%d %d",&n, &m) != 2) return;

    char grid[55][55];
    for (int i = 0; i < n; i++)
    {
        scanf("%s",grid[i]);
    }

    bool possible = true;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < m; c++)
        {
            if (grid[r][c] == '1')
            {
                bool left_full = true;
                for (int k = 0; k < c; k++)
                {
                    if (grid[r][k] == '0')
                    {
                        left_full = false;
                        break;
                    }
                }

                bool top_full = true;
                for (int k = 0; k < r; k++)
                {
                    if (grid[k][c] == '0')
                    {
                        top_full = false;
                        break;
                    }
                }

                if (!left_full && !top_full)
                {
                    possible = false;
                    break;
                }
            }
        }

        if (!possible) break;
    }

    if (possible)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
